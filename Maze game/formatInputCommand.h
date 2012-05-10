//===================================
//include guard
#ifndef FORMATINPUTCOMMAND_H
#define FORMATINPUTCOMMAND_H

//formats a string to make it all lowercase
string formatInputCommand( const string& cmd )
{
    string retval;
    retval.assign(cmd);

    //set lowercase
    for (int i=0;i<retval.length();i++)
            tolower(retval[i]);

    return retval;
}

#endif