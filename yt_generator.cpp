#include "yt_generator.h"

string YT_Generator::generate_command()
{
    string command = ".\\yt-dlp.exe ";

    command += yt_link + " ";

    command += get_quality() + " ";

    if (add_index_prefix){
        command += "-o \"%(playlist_index)s-%(title)s.%(ext)s \" ";
    }

    switch(link_type){
    case Video:
        command += "--no-playlist ";
        break;

    case Playlist:
        command += "--yes-playlist ";

        if (download_type == Range){
            command += "--playlist-items " + to_string(start) + "-" + to_string(end) + " ";
        }

        break;
    }

    command += "-P \"" + path + "\"";

    return command;
}


string YT_Generator::get_quality()
{
    string q{"22 "};

    switch (quality) {
    case AUDIO_ONLY: q = "140 ";
        break;

    case P360: q = "18 ";
        break;

    case P480: q = "244+140 ";
        break;

    case P720: q = "22 ";
        break;

    case P1080: q = "137+140 ";
        break;
    }

    return ("-f " + q);
}
