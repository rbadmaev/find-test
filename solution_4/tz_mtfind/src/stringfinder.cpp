#include "stringfinder.h"

#include <iostream>

void log(const std::string& str)
{
	std::cout << std::this_thread::get_id() << ": " << str << std::endl;
}

StringFinder::StringFinder(int threadCount)
{
	for (size_t i = 0; i < threadCount; ++i) {
		m_threads.emplace_back(std::thread(&StringFinder::process_data_chunk, this));
	}
}
StringFinder::~StringFinder() 
{
}

std::vector<StringFinder::DataOutput> StringFinder::find(const std::string& filename, const std::string& mask)
{
	m_mask = mask;
	m_filestream = std::ifstream(filename, std::ios::in | std::ios::binary);
	int lineidx = 0;
	std::string line;
	while (std::getline(m_filestream, line)) {
		std::lock_guard<std::mutex> lock(input_mutex);
		m_input.push(DataInput(lineidx++, std::move(line)));
		filestream_cv.notify_one();
	}

	m_filestream.close();

	for (auto& thread : m_threads)
	{
		thread.join();
	}
	return m_output;
}

StringFinder::DataOutput StringFinder::find_in_line(const DataInput& data)
{
 	for (size_t i = 0; i < data.text.size(); i++)
	{
		bool match = true;
		for (size_t j = 0; j < m_mask.size(); j++)
		{
			if (m_mask[j] != '?' && data.text[i + j] != m_mask[j])
			{
				match = false;
				break;
			}
		}
		if (match)
		{
			DataOutput fr;
			fr.line_num = data.line_num;
			fr.pos = i;
			fr.text = std::string(data.text.begin() + i, data.text.begin() + i + m_mask.size());
			std::lock_guard<std::mutex> lock(result_mutex);
			m_output.push_back(fr);
			return fr; // if only one match per line, return after 1st match.
		}
	}
	return {};
}

void StringFinder::process_data_chunk()
{	
	while(!m_filestream.eof() || !m_input.empty())
	{
		DataInput data_chunk;
		{
			std::unique_lock<std::mutex> lock(input_mutex);
			filestream_cv.wait_for(lock, std::chrono::milliseconds(100), [&] { return !m_input.empty(); });
			if (!m_input.empty())
			{
				data_chunk = m_input.front();
				m_input.pop();
				find_in_line(data_chunk);
			}
		}
	}
}