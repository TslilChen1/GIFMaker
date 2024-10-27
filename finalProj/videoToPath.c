/*********************************
* Class: MAGSHIMIM Final Project *
* opening the video or new file	 *
**********************************/
#include <stdio.h>
#include <string.h>
#include "videoToPath.h"
#include "linkedList.h"
#define LINE_LENGTH 100
#pragma warning(disable : 4996)

/*removes the '\n' from the end of a string
 input: string
 output: None
 */
void removeNewline(char* str)
{
    int length = strlen(str);

    // check if the last character is a newline
    if (length > 0 && str[length - 1] == '\n')
    {
        // replace the newline with NULL 
        str[length - 1] = '\0';
    }
}

/*
The function save the project in a file
input: a pointer to pointer to struct FrameNode
output: None
*/
void saveProj(FrameNode** video)
{
	char path[STR_SIZE] = { 0 };
	FILE* file = NULL;

	FrameNode* temp = *video;
	char line[LINE_LENGTH] = { 0 };
	char number[10] = { 0 };

	printf("Where to save the project? enter a full path and file name\n");
	myFgets(path, STR_SIZE);

	file = fopen(path, "w");

	if (file != NULL)
	{
		while (temp != NULL)
		{
			strcpy(line, temp->frame->path);

			strcat(line, ",");

			sprintf(number, "%u", temp->frame->duration);
			strcat(line, number);

			strcat(line, ",");

			strcat(line, temp->frame->name);
			strcat(line, "\n");

			fprintf(file, line);

			temp = temp->next;
		}

		fclose(file);
	}
}

/*
The function open an exists file and save it as video with structs
input: None
output: None
*/
FrameNode* oldProj()
{
    FrameNode* video = NULL;
    FrameNode* current = NULL;
    FILE* file = NULL;
    char path[STR_SIZE] = { 0 };
    char name[STR_SIZE] = { 0 };
    unsigned int duration = 0;
    char line[LINE_LENGTH] = { 0 };
    char* token = NULL;
    unsigned int num = 0;
    Frame* image = NULL;


    printf("Enter the path of the project (including project name):\n");
    myFgets(path, STR_SIZE);

    file = fopen(path, "r");

    if (file == NULL)
    {
        printf("Error! Cannot open file. Creating a new project.\n");
        return NULL;
    }
    else
    {
        current = video;

        //read each line from file
        while (fgets(line, sizeof(line), file) != NULL)
        {
            //seperate the data using the srtok func

            token = strtok(line, ",");
            strcpy(path, token);

            token = strtok(NULL, ",");
            duration = atoi(token);

            token = strtok(NULL, ",");
            removeNewline(token);
            strcpy(name, token);
          
            
            if (video == NULL)
            {
                video = addFrameToVideo(&video, name, duration, path);
                current = video;
            }
            else
            {
                current->next = addFrameToVideo(&video, name, duration, path);
                current = current->next;
            }

        }

        fclose(file);
    }

    return video;
}