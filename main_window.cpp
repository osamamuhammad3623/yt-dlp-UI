#include "main_window.h"
#include "ui_main_window.h"
#include <QClipboard>
#include <QFileDialog>
#include <QMessageBox>


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
    ui->plylst_options->setEnabled(true);
}


void Main_Window::on_is_video_clicked()
{
    ui->plylst_options->setEnabled(false);
}


void Main_Window::on_full_playlist_clicked()
{
    ui->from_index->setEnabled(false);
    ui->to_index->setEnabled(false);
}


void Main_Window::on_playlist_range_clicked()
{
    ui->from_index->setEnabled(true);
    ui->to_index->setEnabled(true);
}


void Main_Window::on_generate_clicked()
{
    if (!validate_user_inputs()){
        return;
    }

    QString link = ui->link->text();

    bool add_prefix = (ui->is_plylst->isChecked()) && (ui->add_prefix->isChecked());

    QString download_quality = get_download_quality();

    Command_Configuration config;
    config.link = link;
    config.prefix = add_prefix;
    config.quality = download_quality;

    config.type = get_link_type();
    if (config.type == Range){
        config.from = ui->from_index->value();
        config.to = ui->to_index->value();
    }

    QString download_path = ui->selected_path->text();
    config.path = download_path;


    ui->output->setText(generate_command(config));
}


QString Main_Window::get_download_quality(){
    QString selected_op = ui->quality->currentText();
    QString q = "22"; // default is 720p

    if (selected_op == "1080p"){
        q = "137+140";

    }else if (selected_op == "720p"){
        q = "22";

    }else if (selected_op == "480p"){
        q = "244+140";

    }else if (selected_op == "360p"){
        q = "18";

    }else if (selected_op == "Audio Only"){
        q = "140";
    }

    return q;
}


QString Main_Window::generate_command(Command_Configuration &config){
    QString final_command = "yt-dlp";

    final_command += " " + config.link ;

    final_command += " -f " + config.quality;

    if (config.prefix){
        final_command += " -o \"%(playlist_index)s-%(title)s.%(ext)s \"";
    }

    if (config.type == Playlist){
        final_command += " --yes-playlist ";

    }else if (config.type == Video){
        final_command += " --no-playlist ";

    }else if (config.type == Range){
        final_command += " --playlist-items " + QString::number(config.from) + "-" + QString::number(config.to) + " ";
    }

    final_command += " -P \"" + config.path + "\"";

    return final_command;
}


Link_Type Main_Window::get_link_type(){
    bool is_playlist = ui->is_plylst->isChecked();
    bool is_playlist_full = ui->full_playlist->isChecked();
    bool is_playlist_range = ui->playlist_range->isChecked();

    if (is_playlist && is_playlist_full){
        return Playlist;

    }else if (is_playlist && is_playlist_range){
        return Range;

    }else{
        return Video;
    }
}


bool Main_Window::validate_user_inputs(){
    bool is_valid=true;
    QMessageBox msgBox;
    msgBox.setWindowTitle("Invalid input");

    // Ensure that user chose a link type (playlist or video)
    bool is_plylst = ui->is_plylst->isChecked();
    bool is_video = ui->is_video->isChecked();
    if ((!is_plylst) && (!is_video)){
        msgBox.setText("Choose link type!");
        is_valid= false;
    }

    // ensure that user entered a link
    QString link = ui->link->text();
    if (link.isEmpty()){
        msgBox.setText("Enter a YouTube link!");
        is_valid= false;
    }

    // ensure that user chose a download path/directory
    if (ui->selected_path->text().size() == 0){
        msgBox.setText("Choose download path!");
        is_valid= false;
    }

    bool is_playlist = ui->is_plylst->isChecked();
    bool is_playlist_full = ui->full_playlist->isChecked();
    bool is_playlist_range = ui->playlist_range->isChecked();

    // check link type (if user chose playlist, but didn't specify whether to download the whole playlist or a range of it
    if (is_playlist && ((!is_playlist_full) && (!is_playlist_range))){
        msgBox.setText("Choose to download the whole playlist or a range of it!");
        is_valid= false;
    }

    // ensure the range from/to indices
    if (is_playlist && is_playlist_range){
        int range_from = ui->from_index->value();
        int range_to = ui->to_index->value();
        if (!validate_range(range_from, range_to)){
            msgBox.setText("Invalid range!");
            is_valid= false;
        }
    }

    if (!is_valid){
        msgBox.exec();
    }

    return is_valid;
}


void Main_Window::on_copy_command_clicked()
{
    QClipboard* clpbord = QApplication::clipboard();
    clpbord->setText(ui->output->text());
}


bool Main_Window::validate_range(int from, int to){
    return (to >= from);
}

void Main_Window::on_d_path_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::DirectoryOnly);

    QString selected_dir = "/"; // main partition is the default
    if (dialog.exec()){
        selected_dir = dialog.selectedFiles()[0];
    }
    ui->selected_path->setText(selected_dir);
}

