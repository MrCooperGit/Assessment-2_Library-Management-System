#ifndef FILE_FUNCTIONS_H
#define FILE_FUNCTIONS_H
#include <QString>

class File_Functions
{
public:
    File_Functions();
    void read_file(QString fileName);
    void register_user();
    void update_user();
    void new_book();
    void update_book();
    bool validate_credentials();
    QString display_user();

public slots:
   // void read_file(QString fileName);

};

#endif // FILE_FUNCTIONS_H
