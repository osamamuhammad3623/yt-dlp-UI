#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>


enum Link_Type{
    Video, Playlist, Range
};


struct Command_Configuration{
    QString link;
    bool prefix;
    QString quality;
    QString path;

    Link_Type type;
    int from=0;
    int to=1;
};


QT_BEGIN_NAMESPACE
namespace Ui { class Main_Window; }
QT_END_NAMESPACE

class Main_Window : public QMainWindow
{
    Q_OBJECT

public:
    Main_Window(QWidget *parent = nullptr);
    ~Main_Window();

private slots:
    void on_is_plylst_clicked();

    void on_is_video_clicked();

    void on_full_playlist_clicked();

    void on_playlist_range_clicked();

    void on_generate_clicked();

    void on_d_path_clicked();

    QString get_download_quality();

    /* A function to generate the command based on user-input */
    QString generate_command(Command_Configuration &config);

    /* A function to copy the generated command to Windows clipboard */
    void on_copy_command_clicked();

    /* A function to check the user-input data are valid */
    bool validate_user_inputs();

    /* A function to check the playlist range (starting index < stop index) */
    bool validate_range(int from, int to);

    /* A function to determine the link type: (full playlist, single video or range of a playlist)  */
    Link_Type get_link_type();

private:
    Ui::Main_Window *ui;
};
#endif // MAIN_WINDOW_H
