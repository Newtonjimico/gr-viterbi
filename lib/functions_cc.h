//#include "functions.c"

typedef struct trel{
	char K;
	char G[2];
	char numStates;
	char numhStates;
	char **outputg1;
	char **outputg2;
	char **noutputg1;
	char **noutputg2;

} trellis;

typedef struct nodecd{
	char tracepath;		
} vitstatecd;


typedef struct nodebmsps{
	float bm[2];
	float sp;
	float nsp;		
} vitbmsps;

