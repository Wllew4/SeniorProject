#pragma once

class Log {
    public:
    static void Error(const char* msg);
    static void Print(const char* msg);
    static void AddOn(const char* msg);
};