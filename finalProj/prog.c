/*********************************
* Class: MAGSHIMIM C2			 *
* main 			                 *
**********************************/

#include <stdio.h>
#include "view.h"
#include "linkedList.h"
#include "videoToPath.h"

#pragma warning(disable : 4996)
void menu();
void freeVideoFrames(FrameNode* video);

int main()
{
	char* name = (char*)malloc(STR_SIZE + 1);
	char* path = (char*)malloc(STR_SIZE + 1);
	unsigned int frameDuration = 0;


	FrameNode* video = NULL;
	char nameFrame[STR_SIZE] = { 0 };
	int choice = 0;
	printf("Welcome to Magshimim Movie Maker! what would you like to do?\n");
	printf("[0] Create a new project\n");
	printf("[1] Load existing project\n");
	scanf("%d", &choice);
	getchar();

	if (choice)
	{
		//open an old proj - a proj that is already exists
		video = oldProj();
	}

	do
	{
		//prints to user the menu
		menu();

		//gets the user choice
		printf("Enter your choice: ");
		scanf("%d", &choice);
		getchar();

		switch (choice)
		{
		case 0:
			printf("Bye!");
			getchar();
			break;
		case 1:

			printf("*** Creating a new frame ***\nPlease insert the frame path:\n");
			myFgets(path, STR_SIZE);

			printf("Please insert the frame duration (in milliseconds):\n");
			scanf("%u", &frameDuration);
			getchar();

			printf("Please choose a name for that frame:\n");
			myFgets(name ,STR_SIZE);


			addFrameToVideo(&video, name, frameDuration, path);
			break;
		case 2:
			removeFrameFromVideo(&video);
			break;
		case 3:
			moveFrameInVideo(&video);
			break;
		case 4:
			changeFrameDurationIn1(&video);
			break;
		case 5:
			changeFrameDurationInALL(&video);
			break;
		case 6:
			printFrames(video);
			break;
		case 7:
			play(video);
			printf("\n");
			break;
		case 8:
			saveProj(&video);
			break;
		}
	} while (choice != 0);
	
	freeVideoFrames(video);
	free(name);
	free(path);
	return 0;
}

void menu()
{
	printf("What would you like to do ?\n");
	printf("[0] Exit\n");
	printf("[1] Add new Frame\n");
	printf("[2] Remove a Frame\n");
	printf("[3] Change frame index\n");
	printf("[4] Change frame durationn");
	printf("[5] Change duration of all frames\n");
	printf("[6] List frames\n");
	printf("[7] Play movie!\n");
	printf("[8] Save project\n");
}


void freeVideoFrames(FrameNode* video)
{
	FrameNode* current = video;
	while (current != NULL)
	{
		FrameNode* temp = current;
		current = current->next;
		free(temp->frame->name);
		free(temp->frame->path);
		free(temp->frame->duration);
		free(temp->frame);
		free(temp);
	}
}