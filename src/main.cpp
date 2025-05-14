#include <iostream>
#include <cstdlib>
#include <string>

//#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <dpp/dpp.h>
#include "./httplib.h"

httplib::Client cli("https://api.whatdoestrumpthink.com/api/v1");
const std::string BOT_TOKEN = getenv("BOT_TOKEN");


int main() {
  dpp::cluster bot(BOT_TOKEN);

  bot.on_log(dpp::utility::cout_logger());

  bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {
    if (event.command.get_command_name() == "ping") {
      bot.log(dpp::ll_debug, "Pong!");
      event.reply("Pong!");
    } else if (event.command.get_command_name() == "rowan") {
      // create an embed for my website
      bot.log(dpp::ll_debug, "website request");
      dpp::embed embed = dpp::embed()
        .set_color(dpp::colors::sti_blue)
        .set_title("RowanFoxx's Web Den")
        .set_url("https://gearboxfox.github.io")
        .set_author("RowanFoxx", "", "")
        .set_description("Hey it's that internet fox!")
        .set_thumbnail("https://gearboxfox.github.io/assets/favico.jpg")
        .set_image("https://gearboxfox.github.io/assets/icon.gif")
        .set_timestamp(time(0));

      dpp::message msg(event.command.channel_id, embed);
      event.reply(msg);
    } else if (event.command.get_command_name() == "tronalddump") {
      bot.log(dpp::ll_debug, "attempting to get http request");
      if (auto res = cli.Get("/quotes/random")) {
        // check if restful api request is good
        bot.log(dpp::ll_debug, "request got");
        if (res->status == httplib::StatusCode::OK_200) {
          event.reply("Got a result! Quotes by our favorite peach are coming soon:tm:");
        }
        bot.log(dpp::ll_debug, "request replied");
      } else {
        auto err = res.error();
        bot.log(dpp::ll_debug, "Error got: " + httplib::to_string(err));
        event.reply("Sorry, an error happened TwT");
      }
    }

  });

  bot.on_ready([&bot](const dpp::ready_t& event) {
      //if (dpp::run_once<struct register_bot_commands>()) {
        // clear commands of any cached 

        //bot.global_bulk_command_delete();

        bot.global_command_create(dpp::slashcommand("ping", "Ping pong!", bot.me.id));
        bot.global_command_create(dpp::slashcommand("rowan", "It's me!", bot.me.id));
        bot.global_command_create(dpp::slashcommand("whatdoestrumpthink", "Find a quote by the Tangerine Palpatine", bot.me.id));
      //}
    });

  bot.start(dpp::st_wait);

  return 0;
}
