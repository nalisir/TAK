
//Output to terminal/files
  #include <iostream>
  #include <fstream>
  #include <sstream>
  #include <string>

//Variable format & calculations
  #include <complex.h>
  #include <fftw3.h>

//Declare namespaces
  using namespace std;

class Observable
{

  private:

    // Define the file, save its name for practical reasons
    ofstream outputfile;
    string filename;

    int column_nr; // Number of colums the file will have
    int counter; // Counter is increased everytime we write into the file, until column_nr

  public:

    Observable(string file, int columns, string header)
    {
      this->filename = file + ".txt";
      this->outputfile.open(this->filename, ios::out | ios::trunc);
      this->outputfile.precision(12);

      if(this->outputfile.is_open())
      {
        outputfile << header << "\n";
      }
      else
        cout << "WARNING: Problem creating file " << this->filename << "\n";

      this->column_nr = columns;
      this->counter = 0;
    }
    

    Observable()
    {
    }


    void Initialize(string file, int columns, string header)
    {
      if(this->outputfile.is_open())
        cout << "WARNING: The file " << this->filename << " is already open, cannot initialize!" << "\n";
      else
      {
        this->filename = file + ".txt";
        this->outputfile.open(this->filename, ios::out | ios::trunc);
        this->outputfile.precision(12);

        outputfile << header << "\n";
        this->column_nr = columns;
        this->counter = 0;
        //cout << "File " << this->filename << " created!\n";
      }
    }


    ~Observable()
    {
      //cout << "Output destroy!" << endl;
      this->outputfile.close();
    }
    

  //************************************************************************************
  //
  // Overdefined operator() to handle different types of variable
  //
  //************************************************************************************


    void operator()(double data_entry)
    {
      if(this->outputfile.is_open())
      {
        this->outputfile << data_entry;

        counter++;
        if(counter == column_nr)
        {
          counter = 0;
          this->outputfile << "" << endl;
        }
        else
          this->outputfile << "\t";
      }
      else
        cout << "WARNING: Problem accesing file " << this->filename << "\n";
    }


    void operator()(fftw_complex data_entry)
    {
      if(this->outputfile.is_open())
      {
        this->outputfile << data_entry[0] << "\t" << data_entry[1];

        counter += 2;
        if(counter == column_nr)
        {
          counter = 0;
          this->outputfile << "" << endl;
        }
        else
          this->outputfile << "\t";
      }
      else
        cout << "WARNING: Problem accesing file " << this->filename << "\n";
    }
   

    void operator()(complex<double> data_entry)
    {
      if(this->outputfile.is_open())
      {
        this->outputfile << real(data_entry) << "\t" << imag(data_entry);

        counter += 2;
        if(counter == column_nr)
        {
          counter = 0;
          this->outputfile << "" << endl;
        }
        
        else
          this->outputfile << "\t";
      }
      else
        cout << "WARNING: Problem accesing file " << this->filename << "\n";
    }
    
    
    void operator()(int data_entry)
    {
      if(this->outputfile.is_open())
      {
        this->outputfile << data_entry;

        counter++;
        if(counter == column_nr)
        {
          counter = 0;
          this->outputfile << "" << endl;
        }
        else
          this->outputfile << "\t";
      }
      else
        cout << "WARNING: Problem accesing file " << this->filename << "\n";
    }
    
    
    void operator()(string data_entry)
    {
      if(this->outputfile.is_open())
      {
        this->outputfile << data_entry;

        counter++;
        if(counter == column_nr)
        {
          counter = 0;
          this->outputfile << "" << endl;
        }
        else
          this->outputfile << "\t";
      }
      else
        cout << "WARNING: Problem accesing file " << this->filename << endl;
    }


}; //END OF CLASS
    
