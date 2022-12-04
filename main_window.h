#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>


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

    /* A function to copy the generated command to Windows clipboard */
    void on_copy_command_clicked();

    /* A function to check that the user-input data are valid */
    bool validate_user_inputs();

    void on_link_textChanged(const QString &arg1);

    void on_quality_currentTextChanged(const QString &arg1);

    void on_add_prefix_clicked();

    void on_from_index_valueChanged(int arg1);

    void on_to_index_valueChanged(int arg1);

    void on_open_cmd_clicked();

private:
    Ui::Main_Window *ui;
};
#endif // MAIN_WINDOW_H
