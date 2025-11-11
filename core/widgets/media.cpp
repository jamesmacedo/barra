#include "media.hpp"
#include <memory>
#include <tuple>
#include "core/utils/image.hpp"
#include "core/ui/marquee.cpp"

enum Status {
    Paused,
    Stopped,
    Playing
};

Media::Media(cairo_t *cr) {

  text = std::make_shared<Text>(cr, "");
  icon = std::make_shared<Icon>("/home/nemo/grafico/barra/assets/play.svg", 15, 15);

  auto marquee = std::make_shared<Marquee>(text);

  background = std::make_shared<Container>(2, 4);

  background->add(icon); 
  background->add(text); 

  set_child(background);
};

tuple<string, string> Media::get_current_media(){

    auto dbus_connection = createSessionBusConnection();

    const string playerService = "org.mpris.MediaPlayer2.firefox.instance_1_106";
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
                icon->set_color(make_tuple(255 - std::get<0>(rgb), 255 - std::get<1>(rgb), 255 - std::get<2>(rgb)));
                text->set_color(make_tuple(255 - std::get<0>(rgb), 255 - std::get<1>(rgb), 255 - std::get<2>(rgb)));
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

void Media::draw(cairo_t *cr){
    auto [title, cover] = this->get_current_media();
    if(title != ""){
        text->set_content(cr, title.c_str());
    }
    child->draw(cr);
}
