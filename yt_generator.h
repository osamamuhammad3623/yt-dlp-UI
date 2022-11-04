#ifndef YT_GENERATOR_H
#define YT_GENERATOR_H
#include<string>
using namespace std;

/* Enum for supported qualities */
typedef enum{
    AUDIO_ONLY, P360, P480, P720, P1080
}YT_Quality;

/* Enum for YouTube link type; is it a link to a video or to a playlist */
typedef enum{
    Video, Playlist
}Link_Type;

/* Enum for download type; download the full playlist or a range of it [i.e. first 5 videos, or videos 5 to 9, etc..] */
typedef enum{
    Range, Full_Playlist
}Download_Type;



class YT_Generator
{
public:

    string yt_link{""};
    string path{"/"};
    YT_Quality quality{P720};
    Link_Type link_type{Video};
    Download_Type download_type{Full_Playlist};
    bool add_index_prefix{false};

    uint8_t start{1}, end{2}; // if download_type is Range, those variables are start/end indexes

    std::string generate_command();

private:
    string get_quality();
};

#endif // YT_GENERATOR_H
