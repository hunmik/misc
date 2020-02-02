// Parse config Json file.

#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include "json_parser.h"

// Represents parsed config
struct Config {
  SimpleString<30> wifi_ssid_;
  SimpleString<30> wifi_password_;
  SimpleString<100> duet_ip_;

  void reset() {
    wifi_ssid_.clear();
    wifi_password_.clear();
    duet_ip_.clear();
  }
};

class ConfigParser : public JsonParserListener {
  public:

    // Methods for callbacks from the json parse.
    virtual void OnStartParsing();

    virtual void OnReceivedValue(const char id[], const char val[],
                                 const int arrayDepth, const int indices[]);

    virtual void OnArrayEnd(const char id[], const int arrayDepth,
                            const int indices[]);

    virtual void OnStartReceivedMessage();
    virtual void OnEndReceivedMessage();
    virtual void OnError();

    // Methods for clients

    // Was the message parsed ok?  Verification that required values exist
    // is left to the caller.
    bool IsParsedMessageOk() {
      return config_parser_state_ == MESSAGE_DONE;
    }

    // If the message parsed ok, call this to access internal parsed data.
    const Config& ParsedData() {
      return captured_config_;
    }

    // For debugging
    int State() {
      return config_parser_state_;
    }

  private:
    enum ConfigParserState { IDLE = 1, IN_MESSAGE, MESSAGE_DONE, ERROR };

    bool CheckExpectedState(ConfigParserState expected_state);

    ConfigParserState config_parser_state_;
    Config captured_config_;

};



#endif
