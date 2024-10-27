/*********************************
* Class: MAGSHIMIM Final Project *
* lists of images function		 *
**********************************/

#include <stdio.h>	

#include <stdlib.h>
#include <string.h>

#include "linkedList.h"

#pragma warning(disable : 4996)



/*
The function will get a string ferom the user
input: a string and a len of a string
output:none
*/
void myFgets(char str[], int n)
{
	fgets(str, n + 1, stdin);
	str[strcspn(str, "\n")] = 0;
}

/*
The function creates a struct - Frame thar represents an image
input: a pointer to char (string)- name , duration - unsigned int , and a pointer to char (string)- path
output: a pointer to struct Frame
*/
Frame* createImage(char* name, unsigned int duration, char* path)
{
	Frame* newImage = (Frame*)malloc(sizeof(Frame));

	//allocates memory to path
	newImage->path = (char*)malloc(strlen(name) + 1);
	//allocates memory to name
	newImage->name = (char*)malloc(strlen(name) + 1);

	//copy the name to the struct of Frame
	strcpy(newImage->name, name);
	//copy the nanw to the struct of Frame
	newImage->duration = duration;
	strcpy(newImage->path, path);

	return newImage;
}

/*
The function creates a struct - FrameNode that represents a frame of the gif
input: a struct Frame
output: a pointer to struct Frame
*/
FrameNode* createFrame(Frame* frame)
{
	FrameNode* newFrame = (FrameNode*)malloc(sizeof(FrameNode));

	//save in the Frame the givven frame as param
	newFrame->frame = frame;

	//set the next as NULL
	newFrame->next = NULL;
	return newFrame;
}

/*
The function add a frame to the video
input: a pointer to poniter to struct FrameNode , a pointer to char (string)- name , duration - unsigned int , and a pointer to char (string)- path
output: a pointer to struct FrameNode
*/
FrameNode* addFrameToVideo(FrameNode** video, char* name, unsigned int frameDuration, char* path)
{
	FrameNode* temp = NULL;

	// Check if the frame name already exists in the video
	temp = *video;
	while (temp != NULL)
	{
		if (strcmp(temp->frame->name, name) == 0)
		{
			do
			{
				printf("The name is already taken, please enter another name\n");
				myFgets(name, STR_SIZE);

			} while (strcmp(temp->frame->name, name) == 0);
		}
		temp = temp->next;
	}

	FILE* image = fopen(path, "r");
	if (image == NULL)
	{
		printf("Cannot find the image file. Frame will not be added.\n");
		return NULL;
	}
	else
	{
		//create the image
		Frame* newImage = createImage(name, frameDuration, path);
		//create the frame
		FrameNode* newFrame = createFrame(newImage);

		if (*video != NULL)
		{
			temp = *video;
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = newFrame;
			
		}
		else
		{
			*video = newFrame;
		}

		fclose(image); // Close the file handle
		printf("\n\n");
		return newFrame;
	}
}


/*
The function remove a struct - remove a Frame from video
input: a pointer to pointer to struct FrameNode
output: None
*/
void removeFrameFromVideo(FrameNode** video)
{
	int sign = FALSE;
	FrameNode* current = *video;
	FrameNode* previous = NULL;
	char frameName[STR_SIZE] = { 0 };

	printf("Enter the name of the frame you wish to erase\n");
	myFgets(frameName, STR_SIZE);

	// if the current is not NULL
	if (current != NULL)
	{
		// if there is only 1 frame
		if (strcmp(current->frame->name, frameName) == 0)
		{
			*video = current->next;
			free(current->frame);
			free(current);
			printf("\n\n");
			sign = TRUE;
		}
		else
		{
			// search for the frame in the video
			while (current != NULL)
			{
				if (strcmp(current->frame->name, frameName) == 0)
				{
					previous->next = current->next;
					free(current->frame);
					free(current);
					printf("\n\n");
					sign = TRUE;
				}

				previous = current;
				current = current->next;
			}
		}
	}

	if (!sign)
	{
		printf("The frame was not found\n");
	}
}


/*
The function get the video length
input: a pointer to struct FrameNode
output: the length
*/
int getVideoLength(FrameNode* video) 
{
int length = 0;
FrameNode* current = video;

while (current != NULL) {
	length++;
	current = current->next;
}

return length;
}


/*
The function move Frame In video
input: a pointer to pointer to struct FrameNode
output: None
*/
void moveFrameInVideo(FrameNode** video)
{
	char name[STR_SIZE] = { 0 };
	int newPos = 0;
	int legthOfVideo = 0;
	FrameNode* current = *video;
	FrameNode* previous = NULL;
	int currentPos = 1;

	printf("Enter the name of the frame\n");
	myFgets(name, STR_SIZE);

	printf("Enter the new index in the movie you wish to place the frame\n");
	scanf("%d", &newPos);

	while (current != NULL && strcmp(current->frame->name, name) != 0)
	{
		previous = current;
		current = current->next;
		currentPos++;
	}

	legthOfVideo = getVideoLength(*video);

	if (current == NULL)
	{
		printf("this frame does not exist");

	}
	else if (newPos < 1 || newPos > getVideoLength)
	{
		printf("The movie contains only %d frames!", legthOfVideo);
	}

	else if (currentPos != newPos)
	{
		if (previous == NULL) 
		{
			*video = current->next;
		}
		else 
		{
			previous->next = current->next;
		}
	}

	//save the frame at the new position
	FrameNode* newPrevious = NULL;
	FrameNode* newCurrent = *video;
	int newCurrentPosition = 1;

	while (newCurrentPosition < newPos && newCurrent != NULL)
	{
		newPrevious = newCurrent;
		newCurrent = newCurrent->next;
		newCurrentPosition++;
	}

	if (newPrevious == NULL)
	{
		current->next = *video;
		*video = current;
	}
	else
	{
		newPrevious->next = current;
		current->next = newCurrent;
	}

	printf("Frame '%s' moved to position %d.\n", name, newPos);
}


/*
The function change the duration
input: a pointer to struct FrameNode and unsigned int duration
output: None
*/
void changeFrameDuration(FrameNode* video, unsigned int duration)
{
	if (video != NULL)
	{
		video->frame->duration = duration;
	}

}

/*
The function change the Frame duration in 1
input: a pointer to pointer to struct FrameNode 
output: None
*/
void changeFrameDurationIn1(FrameNode** video)
{
	unsigned int duration = 0;
	FrameNode* temp = *video;
	char nameFrame[STR_SIZE] = { 0 };

	printf("enter the name of the frame\n");
	myFgets(nameFrame, STR_SIZE);

	//runing until catch the name that the user wanted to change
	while (temp->next != NULL && strcmp(temp->frame->name, nameFrame) != 0)
	{
		temp = temp->next;
	}

	if (temp->next == NULL && strcmp(temp->frame->name, nameFrame) != 0)
	{
		printf("The frame does not exist");
	}
	else
	{
		printf("Enter the new duration\n");
		scanf("%u", &duration);
		changeFrameDuration(temp, duration);
	}
}


/*
The function change the Frame duration in all
input: a pointer to pointer to struct FrameNode
output: None
*/
void changeFrameDurationInALL(FrameNode** video)
{
	FrameNode* temp = *video;
	unsigned int duration = 0;

	printf("Enter the duration for all frames:\n");
	scanf("%u", &duration);
	getchar();

	while (temp != NULL)
	{
		changeFrameDuration(temp, duration);
		temp = temp->next;
	}
}


/*
The function prints the list of frames
input: a pointer to struct FrameNode
output: None
*/
void printFrames(FrameNode* video)
{
	FrameNode* temp = video;
	printf("                Name            Duration        Path\n");

	while (temp != NULL)
	{
		printf("                 %s             %d ms           %s\n", temp->frame->name, temp->frame->duration, temp->frame->path);
		temp = temp->next;
	}
}

