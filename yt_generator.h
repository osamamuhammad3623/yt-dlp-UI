#ifndef YT_GENERATOR_H
#define YT_GENERATOR_H
#include<string>
using namespace std;


typedef enum{
    AUDIO_ONLY, P360, P480, P720, P1080
}YT_Quality;

typedef enum{
    Video, Playlist
}Link_Type;

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

    uint8_t start{1}, end{2};

    std::string generate_command();

private:
    string get_quality();
};

#endif // YT_GENERATOR_H
