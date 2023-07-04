#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
unordered_map<int, string> rec;




// ---------------------------------------------------

void commit()
{
    //write all map datastructure values into the file.
    ofstream write;
    write.open("record.txt");
    for (auto it : rec)
    {
        write << it.first << "," << it.second << "\n";
    }
}
// ---------------------------------------------------
void separateValues(string s)
{

    // function takes in an input string of one line from a myfile and returns void type, inserts respective keys and values into the map.

    int key;

    string str = s;

    stringstream myTuple(str);
    bool flag = false;

    // while input stream is good, no errors
    while (myTuple.good())
    {
        string substr;

        getline(myTuple, substr, ',');

        if (flag == false)
        {
            // check if i have a key or a value

            for (int i = 0; i < substr.size(); i++)
            {
                if (!isdigit(substr[i]))
                {
                    cout << " Invalid Key \n";
                    return;
                }
            }

            key = stoi(substr);
            flag = true;
        }

        else
        {
            // load my key,value pair in map
            rec[key] = substr;
            flag = false;
        }
    }

    //   for (auto x : rec){
    //       cout << x.first << " | " << x.second << endl;

    //   }
}

// ---------------------------------------------------
bool load(string path)
{
    //Load Function - loads all records from the given file 
    ifstream myfile; // creating an ifstream object
    string line;     // for reading myfile line by line
    

    // opening the myfile
    myfile.open(path);

    if (!myfile.is_open())
    {
        return false; // when myfile is not opened return false
    }
    else
    { // when myfile is opened

        while (!myfile.eof())
        {
            
            if(rec.size()> 1000000){

                cout << "MAX LIMIT EXCEEDED \n";
                return false;
            }
            
            getline(myfile, line);
            if (line.empty())
            {
                break;
            }
            else
            {
                separateValues(line);
            }
        }

        myfile.close();
        commit();
        return true;
    }
}

// ---------------------------------------------------
void dataInilizatation()
{
    //record.txt is the database file
    ifstream myfile; // creating an ifstream object
    string line;     // for reading myfile line by line

    // opening the myfile
    myfile.open("record.txt");

    while (!myfile.eof())
    {

        getline(myfile, line);
        if (line.empty())
        {
            break;
        }
        else
        {
            separateValues(line);
        }
    }

    myfile.close();
}

// ---------------------------------------------------
string scanMax(int start, int end)
{
    //scanMax to compare values between the enterred key values
    string max = "";
    

    for (int i = start; i <= end; i++)
    {

        if (rec.find(i) != rec.end())
        {

            if (max.compare(rec[i]) < 0)
            {
                max = rec[i];
            }
        }
    }
    if (max==""){
        // cout<<"Maximum not Found\n";
        return max;
    }

    return max;
}

// ---------------------------------------------------
bool putData()
{
    //add given record
    int key;
    string value;
    cout << "\n Enter key : ";
        cin >> key;

        if(rec.size()>1000000){
            cout << "MAX LIMIT EXCEEDED \n";
            return false;
        }
        cout << "\n Enter value: ";
        cin >> value;

        rec[key] = value;
        ofstream write;
        write.open("record.txt", ios::app);
        if (rec.find(key) == rec.end())
        {

            write << key << "," << value << "\n";

            write.close();
        }
        else
        {
            rec[key] = value;
            commit();
        }
        write.close();
        return true;
       
       
        }
    
 

// --------------------------------------------------------------------
string getData()
{
    //Find the value of key if found otherwise specify Not Found
    int key;
    cout << "\nEnter the value of key : ";
    cin >> key;

    if (rec.find(key) == rec.end())
    {  
        cout << "\nRecord Not Found";
        return NULL;
    }
    else
    {

        cout << "\nValue According to key : " << key << " is " << rec[key];
        cout << endl
             << endl;
    }
    
    return rec[key];
}

int main(int argc, char const *argv[])
{
    //Driver Program
    int choice;
    string path,x;

    dataInilizatation();
    while (true)
    {
        cout << "\n----------------------------------------------------";
        cout << "\n\t\tDatabase Operations";
        cout << "\n----------------------------------------------------\n";
        cout << "\n1.Put";
        cout << "\n2.Get";
        cout << "\n3.Load";
        cout << "\n4.ScanMax";
        cout << "\n5.Exit";

        cout << "\n\nEnter your choice : ";
        cin >> choice;
        cout << "\n----------------------------------------------------\n";

        switch (choice)
        {
        case 1:
            if (putData())
            {
                cout << "\nRecord inserted Sucessfully";
                cout << endl
                     << endl;
            }
            else
            {
                cout << "\n Failed To Insert";
            }

            break;
        case 2:
            getData();
            break;

        case 3:

            cout << "Please enter the file path: " << endl;
            cin >> path;
            if (load(path) == true)
            {
                cout << "Loaded successfully" << endl;
            }
            else
            {
                cout << "Load function unsuccessful" << endl;
            }
            load(path);
            break;
        case 4:
            int start, end;
            cout << "\nEnter start : ";
            cin >> start;
            cout << "\nEnter end : ";
            cin >> end;
            x=scanMax(start, end);
            if (x!="")
            {
                cout << "\n"
                 << "Maximum string : " <<x ;
            }
            else{
                cout<<"No String Found\n";
            }

            break;
        case 5:
            cout << "\n Exited Succesfully";
            cout << "\n\n----------------------------------------------------\n";
            exit(1);
            break;
        }
    }

    return 0;
}
