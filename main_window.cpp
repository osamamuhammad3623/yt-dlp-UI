#include "main_window.h"
#include "ui_main_window.h"
#include <QClipboard>


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

    bool video_link = (ui->is_video->isChecked());
    bool playlist_link = (ui->is_plylst->isChecked());

    bool add_prefix = (ui->is_plylst->isChecked()) && (ui->add_prefix->isChecked());

    QString download_quality = get_download_quality();

    bool full_playlist = playlist_link && (ui->full_playlist->isChecked());


    Command_Configuration config;
    config.link = link;
    config.prefix = add_prefix;
    config.quality = download_quality;

    if (full_playlist){
        config.full_plylst = Playlist;

    }else if (video_link){
        config.full_plylst = Video;

    }else if (playlist_link && ui->playlist_range->isChecked()){
        config.full_plylst = Range;
        int range_from = ui->from_index->value();
        int range_to = ui->to_index->value();
        if (validate_range(range_from, range_to)){
            config.from = range_from;
            config.to = range_to;
        }else{
            return;
        }
    }


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

    if (config.full_plylst == Playlist){
        final_command += " --yes-playlist ";

    }else if (config.full_plylst == Video){
        final_command += " --no-playlist ";

    }else if (config.full_plylst == Range){
        final_command += " --playlist-items " + QString::number(config.from) + "-" + QString::number(config.to) + " ";
    }

    return final_command;
}


bool Main_Window::validate_user_inputs(){

    // Ensure that user chose a link type (playlist or video)
    bool is_plylst = ui->is_plylst->isChecked();
    bool is_video = ui->is_video->isChecked();
    if ((!is_plylst) && (!is_video)){
        return false;
    }

    // ensure that user entered a link
    QString link = ui->link->text();
    if (link.isEmpty()){
        return false;
    }

    return true;
}


void Main_Window::on_copy_command_clicked()
{
    QClipboard* clpbord = QApplication::clipboard();
    clpbord->setText(ui->output->text());
}


bool Main_Window::validate_range(int f, int t){
    return (t >= f);
}
