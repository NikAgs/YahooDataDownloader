//
//  main.cpp
//  YahooFinanceExtractor
//
//  Modified by Nikhil Agarwal on 2014-07-11.
//  Copyright (c) 2014 Nikhil Agarwal. All rights reserved.
//


#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <stdio.h>
#include <curl/curl.h>
//#include <curl/types.h>
#include <curl/easy.h>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main(void) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    cout<<"Enter output file directory (e.g. /Users/Downloads/sample.csv)"<<endl;
    string outfilename;
    cin>>outfilename;
    string dummy;
    getline(cin, dummy);
    cout<<"Enter stock symbols, seperated by space (e.g. GOOG FB)"<<endl;
    string stock_line;
    getline(cin, stock_line);
    stringstream ss(stock_line);
    string url="http://download.finance.yahoo.com/d/quotes.csv?s=%40%5EDJI";
    string stock_symbol;
    while(ss>>stock_symbol){
        url+=","+stock_symbol;
    }
    url+="&f=nspobat8mwva2j1re7d&e=.csv";
    
    ofstream MyFile;
    MyFile.open (outfilename.c_str(), ios::out | ios::ate | ios::app | ios::binary) ;
    MyFile<<"Name,Symbol,";
    MyFile<<"PreviousClose,Open,Bid,Ask,OneyrTargetPrice,DaysRange,YearRange,Volume,AverageDailyVolume,MarketCapitalization,PERatio,PEGRatio,EPSEstimateCurrentYear,ShortRatio"<<endl;
    
    MyFile.close();
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(outfilename.c_str(),"ab");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }
    return 0;
}