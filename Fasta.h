// ***************************************************************************
// FastaIndex.h (c) 2010 Erik Garrison <erik.garrison@bc.edu>
// Marth Lab, Department of Biology, Boston College
// All rights reserved.
// ---------------------------------------------------------------------------
// Last modified: 5 February 2010 (EG)
// ---------------------------------------------------------------------------

#ifndef _FASTA_H
#define _FASTA_H

#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <boost/algorithm/string.hpp>
//#include <boost/algorithm/string/erase.hpp>
#include <boost/lexical_cast.hpp>
#include "LargeFileSupport.h"
#include <sys/stat.h>


using namespace std;
using boost::lexical_cast;

class FastaIndexEntry {
    friend ostream& operator<<(ostream& output, const FastaIndexEntry& e);
    public:
        FastaIndexEntry(string name, int length, long long offset, int line_blen, int line_len);
        FastaIndexEntry(void);
        ~FastaIndexEntry(void);
        string name;  // sequence name
        int length;  // length of sequence
        long long offset;  // bytes offset of sequence from start of file
        int line_blen;  // line length in bytes, sequence characters
        int line_len;  // line length including newline
        void clear(void);
};

class FastaIndex: public map<string, FastaIndexEntry>{
    friend ostream& operator<<(ostream& output, const FastaIndex& i);
    public:
        FastaIndex(void);
        ~FastaIndex(void);
        void indexReference(string refName);
        void readIndexFile(string fname);
        void writeIndexFile(string fname);
        ifstream indexFile;
        FastaIndexEntry entry(string key);
        void flushEntryToIndex(FastaIndexEntry& entry);
        string indexFileExtension(void);
};

class FastaReference {
    public:
        FastaReference(string reffilename);
        string filename;
        ~FastaReference(void);
        FILE* file;
        FastaIndex* index;
        vector<FastaIndexEntry> findSequencesStartingWith(string seqnameStart);
        string getSequence(string seqname);
        // potentially useful for performance, investigate
        // void getSequence(string seqname, string& sequence);
        string getSubSequence(string seqname, int start, int length);
        string sequenceNameStartingWith(string seqnameStart);
        long unsigned int sequenceLength(string seqname);
};

#endif

