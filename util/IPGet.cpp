#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#include<sys/ioctl.h>

#include<sys/socket.h>

#include<arpa/inet.h>

#include<netinet/in.h>

#include<net/if.h>

#include <unistd.h>

#include"CProperty.h"

#include<string>

using namespace std;
//char* getip(char* ip_buf)
char* getIP(char* ip_buf)

{


    struct ifreq temp;


    struct sockaddr_in *myaddr;


    int fd = 0;


    int ret = -1;


    strcpy(temp.ifr_name, "eth0");


    if((fd=socket(AF_INET, SOCK_STREAM, 0))<0)


    {


        return NULL;


    }


    ret = ioctl(fd, SIOCGIFADDR, &temp);


    close(fd);


    if(ret < 0)


        return NULL;


    myaddr = (struct sockaddr_in *)&(temp.ifr_addr);

    strcpy(ip_buf, inet_ntoa(myaddr->sin_addr));

    printf("ip_buf = %s\n",ip_buf);


    return ip_buf;


};

char *get_ip()
{
    int fd, num;
    struct ifreq ifq[16];
    struct ifconf ifc;
    int i;
    char *ips, *tmp_ip;
    char *delim = ",";
    int val;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd < 0)
    {
        fprintf(stderr, "socket failed\n");
        return NULL;
    }
    ifc.ifc_len = sizeof(ifq);
    ifc.ifc_buf = (caddr_t)ifq;
    if(ioctl(fd, SIOCGIFCONF, (char *)&ifc))
    {
        fprintf(stderr, "ioctl failed\n");
        return NULL;
    }
    num = ifc.ifc_len / sizeof(struct ifreq);
    if(ioctl(fd, SIOCGIFADDR, (char *)&ifq[num-1]))
    {
        fprintf(stderr, "ioctl failed\n");
        return NULL;
    }
    close(fd);

    val = 0;
    for(i=0; i<num; i++)
    {
        tmp_ip = inet_ntoa(((struct sockaddr_in*)(&ifq[i].ifr_addr))-> sin_addr);
        if(strcmp(tmp_ip, "127.0.0.1") != 0)
        {
            val++;
        }
    }

    ips = (char *)malloc(val * 16 * sizeof(char));
    if(ips == NULL)
    {
        fprintf(stderr, "malloc failed\n");
        return NULL;
    }
    memset(ips, 0, val * 16 * sizeof(char));
    val = 0;
    for(i=0; i<num; i++)
    {
        tmp_ip = inet_ntoa(((struct sockaddr_in*)(&ifq[i].ifr_addr))-> sin_addr);
        if(strcmp(tmp_ip, "127.0.0.1") != 0)
        {
            if(val > 0)
            {
                strcat(ips, delim);
            }
            strcat(ips, tmp_ip);
            val ++;
        }
    }

		PropertyUtil::PropertyMapT pmt;
    	PropertyUtil::read("UpNodeAddress.properties",pmt);
    	string localip = PropertyUtil::getPropery(pmt,"localip");
    	ips = const_cast<char*>(localip.c_str());

    return ips;
}
