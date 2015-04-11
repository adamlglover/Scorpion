// This program will use a native thread to execute code
import io;
import thread;

protected shareable int x, y, param, area;
int main()
{
  Thread thread;
  thread.run(){
     // encapsulated code here
     x = 5;
     y = 8;
     param = x + y;
     area = x * y; // calculate area and parameter and share the data with 
  }
  thread.start();
  out << "The parameter is: " << param << "\nThe area is: " << area;
  return  0;
}

