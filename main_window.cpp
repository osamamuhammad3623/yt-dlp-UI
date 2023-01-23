#include "main_window.h"
#include "ui_main_window.h"
#include <QClipboard>
#include <QFileDialog>
#include <QMessageBox>
#include "yt_generator.h"
#include "QProcess"

YT_Generator command_generator;

Main_Window::Main_Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Main_Window)
{
    ui->setupUi(this);
}

Main_Window::~Main_Window()
{
    delete ui;
}

void Main_Window::on_is_plylst_clicked()
{
    // enable playlist options
    ui->plylst_options->setEnabled(true);
    command_generator.link_type = Playlist;
}

void Main_Window::on_is_video_clicked()
{
    // disable playlist options
    ui->plylst_options->setEnabled(false);
    command_generator.link_type = Video;
}


void Main_Window::on_full_playlist_clicked()
{
    // disable playlist range indices
    ui->from_index->setEnabled(false);
    ui->to_index->setEnabled(false);

    command_generator.download_type = Full_Playlist;
}

void Main_Window::on_playlist_range_clicked()
{
    // enable playlist range indices
    ui->from_index->setEnabled(true);
    ui->to_index->setEnabled(true);

    command_generator.download_type = Range;
}


void Main_Window::on_generate_clicked()
{

    // first, validate user-input data
    if (!validate_user_inputs()){
        return;
    }

    ui->output->setText(QString::fromStdString(command_generator.generate_command()));
}

bool Main_Window::validate_user_inputs(){
    bool is_valid=true;
    QMessageBox msgBox;
    msgBox.setWindowTitle("Invalid input");

    // ensure that user entered a link
    QString link = ui->link->text();
    if (link.isEmpty()){
        msgBox.setText("Enter a YouTube link!");
        is_valid= false;
    }

    // ensure that user chose a download path/directory
    if (ui->selected_path->text().size() < 2){
        msgBox.setText("Choose download path!");
        is_valid= false;
    }

    if (ui->from_index->value() >= ui->to_index->value()){
        msgBox.setText("Download range is invalid");
        is_valid= false;
    }

    if (!is_valid){
        msgBox.exec();
    }

    return is_valid;
}

void Main_Window::on_copy_command_clicked()
{
    // copy the generated command to clipboard
    QClipboard* clpbord = QApplication::clipboard();
    clpbord->setText(ui->output->text());
}

void Main_Window::on_d_path_clicked()
{
    // open a file dialog that accepts directories only
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);

    QString selected_dir = "/"; // main partition is the default (C)
    if (dialog.exec()){
        selected_dir = dialog.selectedFiles()[0];
    }
    ui->selected_path->setText(selected_dir); // diplay the selected path to the user

    command_generator.path = selected_dir.toStdString();
}


void Main_Window::on_link_textChanged(const QString &arg1)
{
    command_generator.yt_link = arg1.toStdString();
}


void Main_Window::on_quality_currentTextChanged(const QString &arg1)
{
    QString selected_op = arg1;

    if (selected_op == "1080p"){
        command_generator.quality = P1080;

    }else if (selected_op == "720p"){
        command_generator.quality = P720;

    }else if (selected_op == "480p"){
        command_generator.quality = P480;

    }else if (selected_op == "360p"){
        command_generator.quality = P360;

    }else if (selected_op == "Audio Only"){
        command_generator.quality = AUDIO_ONLY;
    }
}


void Main_Window::on_add_prefix_clicked()
{
    if (ui->add_prefix->isChecked()){
        command_generator.add_index_prefix = true;
    }else{
        command_generator.add_index_prefix = false;
    }
}


void Main_Window::on_from_index_valueChanged(int arg1)
{
    command_generator.start = arg1;
}


void Main_Window::on_to_index_valueChanged(int arg1)
{
    command_generator.end = arg1;
}


void Main_Window::on_open_cmd_clicked()
{
    // launch an external CMD/terminal, user should just paste the generated command in it

    // on windows
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    QStringList args;
    args << "/C" << "start";
    QProcess::startDetached("cmd", args);
#else
    // on linux
    system("gnome-terminal --window");
#endif
}


void Main_Window::on_download_desc_clicked()
{
    if(ui->download_desc->isChecked()){
        command_generator.download_description=true;
    }
}

