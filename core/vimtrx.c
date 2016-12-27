#include "vimtrx.h"

class ChannelVision{
	private:
		string id;
		int idx;
	public:
		ChannelVision(void){
			id = "";
			idx = 0;
		}

};

class VMatrix{
	private:
		ChannelVision input [CHAN_IN];
		ChannelVision output [CHAN_OUT];
	public:
		VMatrix(){
		}
	public:
	ChannelVision getChanIn(string id){
		return input[0];
	}
	ChannelVision getChanOut(string id){
		return output[1];
	}
		
};

int main(){
	printf("hello world");
}
