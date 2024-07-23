#pragma once
#include <string>
#include <vector>
#include <thread>
#include <unordered_map>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <fstream>


class StringFinder
{
public:
	StringFinder(int threadCount);
	~StringFinder();
	struct DataOutput
	{
		int line_num = -1;
		int pos = -1;
		std::string text;
		DataOutput() {}
		DataOutput(int ln, int p, const std::string& t) : line_num(ln), pos(p), text(t) {}
	};

	std::vector<DataOutput> find(const std::string& filename, const std::string& mask);

private:
	struct DataInput
	{
		int line_num = -1;
		std::string text;
		DataInput() {}
		DataInput(int ln, const std::string& t) : line_num(ln), text(t) {}
	};

	std::string m_mask;
	std::vector<std::thread> m_threads;

	std::mutex result_mutex;
	std::condition_variable output_cv;
	std::vector<DataOutput> m_output;

	std::condition_variable filestream_cv;
	std::ifstream m_filestream;

	std::mutex input_mutex;
	std::queue<DataInput> m_input;

	DataOutput find_in_line(const DataInput& data);
	void process_data_chunk();
};