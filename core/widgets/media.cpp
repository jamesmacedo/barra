#include "media.hpp"
#include <tuple>
#include "core/utils/image.hpp"

enum Status {
    Paused,
    Stopped,
    Playing
};

tuple<string, string> Media::get_current_media(){

    auto dbus_connection = createSessionBusConnection();

    const string playerService = "org.mpris.MediaPlayer2.firefox.instance_1_108";
    const string playerPath = "/org/mpris/MediaPlayer2";
    const string playerInterface = "org.mpris.MediaPlayer2.Player";

    try {
        auto proxy = createProxy(*dbus_connection, playerService, playerPath);

        sdbus::Variant playbackStatus;
        proxy->callMethod("Get")
            .onInterface("org.freedesktop.DBus.Properties")
            .withArguments(playerInterface, "PlaybackStatus")
            .storeResultsTo(playbackStatus);


        string status = playbackStatus.get<string>();
        cout << "Status: " << status << endl;

        if(status != "Paused"){
            sdbus::Variant metadataVariant;
            proxy->callMethod("Get")
                .onInterface("org.freedesktop.DBus.Properties")
                .withArguments(playerInterface, "Metadata")
                .storeResultsTo(metadataVariant);

            auto metadata = metadataVariant.get<map<string, sdbus::Variant>>();

            auto title = metadata.at("xesam:title").get<string>();
            if(title != current_title){
                current_title = title;
                string cover = metadata.at("mpris:artUrl").get<string>();
                cover.erase(0, 7);
                auto rgb = load_image(cover);
                background->set_color(rgb);
                return {title, cover};
            }
        }

        return {"", ""};
    } catch (const sdbus::Error &e) {
        cerr << "Error: " << e.getName() << " - " << e.getMessage() << '\n';
        exit(1);
    }
}

Media::Media(cairo_t *cr) {

  text = std::make_shared<Text>(cr, "Nothing playing...");

  std::vector<std::shared_ptr<Widget>> children = {
    text 
  };

  background = std::make_shared<Container>(children, 2);
  set_child(background);
};

void Media::draw(cairo_t *cr){
    auto [title, cover] = this->get_current_media();
    if(title != ""){
        text->set_content(cr, title.c_str());
    }
    child->draw(cr);
}
