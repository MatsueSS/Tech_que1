#include "Table.h"
#include "Session.h"
#include "FileException.h"
#include "BadValueExcept.h"

void start(std::string filename)
{
    try{
        Session wd("../res/" + filename); //Входной файл
        wd.start_day(); 
    } catch (const FileException& error) {
        std::cerr << "File error: " << error.what() << '\n';
    } catch(const BadValueExcept& error) {
        std::cerr << "Error with bad value: " << error.what() << '\n';
    } catch (const std::exception& error) {
        std::cerr << "Unexpected error: " << error.what() << '\n';
    }

    return;
}

int main(int argc, char** argv)
{
    start(argv[1]);

    return 0;
}