#include "main_window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Main_Window w;
    w.setWindowTitle("yt-dlp Command Generator & Downloader");
    w.show();
    return a.exec();
}
