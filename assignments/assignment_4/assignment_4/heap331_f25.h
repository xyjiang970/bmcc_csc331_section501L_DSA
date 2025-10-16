// heap331.h
// 3-10-2025 c++ heap class
using namespace std;
class heapType{
  public:
    int elementsinheap();
    bool empty();
    string front();
    bool full();
    heapType();
    void pop();
    void push(string newticket);
  private:
    int C1I;   // child 1 index
    int C2I;   // child 2 index
    int CI;    // child index
    int count; // elements in the heap
    int done;  // status flag
    int EOL;   // end of line
    string heap[10];
    int PI;    // parent index
    void swap(int I1,int I2); // exchange heap contents
};
// -----------------------------------------------------
// -----------------------------------------------------
int heapType::elementsinheap(){
  return count;
}
// -----------------------------------------------------
bool heapType::empty(){
  return count == 0;
}
// -----------------------------------------------------
string heapType::front(){
  if(count == 0){
    cout << "front() failed ... heap is empty.\n";
    return 0;
  }
  else
    return heap[0];
}
// -----------------------------------------------------
bool heapType::full(){
  return count == 10;
}
// -----------------------------------------------------
heapType::heapType(){ //default constructor
  EOL=0; count=0;
  for(int i=0; i<10; i++)
    heap[i]="";
}
// -----------------------------------------------------
void heapType::pop(){
  if(count == 0)
    cout << "pop() failed ... heap is empty.\n";
  else{
    if(count == 1){
      count=0; EOL=0; heap[0]="";
    }
    else{
      if(count == 2){
        count=1; EOL=1; heap[0]=heap[1]; heap[1]="";
      }
      else{
        count--; EOL--; heap[0]=heap[EOL];
        heap[EOL]=""; done=0; PI=0; C1I=1; C2I=2;
        while (!done){
   	    if(C2I >= EOL){
  	      if(heap[PI] > heap[C1I])
  	        swap(PI,C1I);
  	      done=1;
  	    }
  	    else{
	      if((heap[PI]<=heap[C1I])&&(heap[PI]<=heap[C2I]))
	        done=1;
	      else{
	        if(heap[C1I]<heap[C2I]){
	          swap(PI,C1I);
	          if((C1I*2+1)>=EOL)
		      done=1;
	          else
		      PI=C1I;
	        }
	        else{
	          swap(PI,C2I);
	          if((C2I*2+1)>=EOL)
		      done=1;
	          else
		      PI=C2I;
	        }
	        C1I=PI*2+1; C2I=PI*2+2;
	      }
	    }
        } // while loop
      } // if count==2
    } // if count==1
  } // if count==0
}
// -----------------------------------------------------
void heapType::push(string newticket){
  if(count == 10){
    cout << "push(" << newticket << ") failed ... heap is full." << endl;
  }
  else{
    count++;
    heap[EOL]=newticket;
    CI=EOL;
    EOL++;
    done=0;
    while(!done){
      if(CI==0)
	done=1;
      else{
        PI=(CI-1)/2;
	if(heap[PI]<=heap[CI])
	  done=1;
	else{
	  swap(PI,CI);
	  CI=PI;
	}
      } // if CI==0
    } // while
  } // if count==10
}
// -----------------------------------------------------
void heapType::swap(int I1,int I2){ // exchange heap contents
  string T=heap[I1];
  heap[I1]=heap[I2];
  heap[I2]=T;
}
