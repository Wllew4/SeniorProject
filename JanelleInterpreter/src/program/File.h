#pragma once

class File {
	private:
		char* m_file;
	public:
    void load(char* file);
    void execute();
};