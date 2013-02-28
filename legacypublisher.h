#ifndef LEGACY_PUBLISHER_H
#define LEGACY_PUBLISHER_H

#include "noncopyable.h"
#include "publisher.h"
#include "referee.pb.h"
#include "udpbroadcast.h"

class Configuration;
class Logger;
class SaveState;

class LegacyPublisher : public NonCopyable, public Publisher {
	public:
		LegacyPublisher(const Configuration &configuration, Logger &logger);
		void publish(SaveState &state);

	private:
		UDPBroadcast bcast;
		uint8_t counter;
		char cached_command_char;
		Referee::Stage last_stage;
		Referee::Command last_command;
		int last_yellow_ycards, last_blue_ycards;
		unsigned int last_yellow_rcards, last_blue_rcards;

		char compute_command(const Referee &state);
};

#endif

