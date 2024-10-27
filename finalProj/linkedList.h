#ifndef LINKEDLISTH
#define LINKEDLISTH

#define FALSE 0
#define TRUE !FALSE
#define STR_SIZE 100

// Frame struct
typedef struct Frame
{
	char* name;
	unsigned int duration;
	char* path;
} Frame;


// Link (node) struct
typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;

void myFgets(char str[], int n);
Frame* createImage(char* name, unsigned int duration, char* path);
FrameNode* createFrame(Frame* frame);
FrameNode* addFrameToVideo(FrameNode** video, char* name, unsigned int frameDuration, char* path);
void removeFrameFromVideo(FrameNode** video);
int getVideoLength(FrameNode* video);
void moveFrameInVideo(FrameNode** video);
void changeFrameDuration(FrameNode* video, unsigned int duration);
void changeFrameDurationIn1(FrameNode** video);
void changeFrameDurationInALL(FrameNode** video);
void printFrames(FrameNode* video);

#endif