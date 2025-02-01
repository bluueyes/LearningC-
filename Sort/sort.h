#include <iostream>
#include <vector>
#include <algorithm>

//选择排序 不稳定
void selectSort(std::vector<int>& vec){

  int n=vec.size();
  for(int i=0;i<n-1;i++){
    for(int j=i+1;j<n;j++){
      if(vec[i]>vec[j]){
        std::swap(vec[i],vec[j]);
      }
    }
  }
}

//冒泡排序 稳定
void popSort(std::vector<int>& vec){

  int n=vec.size();
  for(int i=0;i<n;i++){
    for(int j=n-1;j>i;j--){
      if(vec[j]<vec[j-1]){
        std::swap(vec[j],vec[j-1]);
      }
    }
  }
}

//插入排序 稳定
void insertSort(std::vector<int>& vec){

  int n=vec.size();
  for(int i=1;i<n;i++){
    for(int j=i;j>1;j--){
      if(vec[j]<vec[j-1]){
        std::swap(vec[j],vec[j-1]);
      }
      else{
        break;
      }
    }
  }
}

//希尔排序
void shellSort(std::vector<int>& vec){
  int n=vec.size();
  
  for(int gap=n/2;gap>0;gap/=2){
    for(int i=gap;i<n;i++){
      
      for(int j=i;j>gap&&vec[j-gap]>vec[j];j-=gap){
        std::swap(vec[j-gap],vec[j]);
      }
    } 
  }
}


//快速排序 不稳定
void QuickSort(std::vector<int>& vec,int left,int right){
  if(left==right) return;
  int left_=left+1;
  int right_=right;
  int temp=vec[left];

  while(left_<right_){
    while(left_<right_ && vec[right_]>temp){
      right_--;
    }
    while(left_<right_ && vec[left_]<=temp){
      left_++;
    }
    if(left_!=right_){
      std::swap(vec[right_],vec[left_]);
    }

  }
  
  std::swap(vec[left_],vec[left]);
  QuickSort(vec,left,left_-1);
  QuickSort(vec,right_+1,right);  
}

void quickSort(std::vector<int>& vec){
  
  QuickSort(vec,0,vec.size()); 
}

//归并排序
void Merge(std::vector<int>& vec,int left,int mid,int right){
  
  int n1=mid-left+1;  //左边的大小
  int n2=right-mid;   //右边的大小

  std::vector<int> vec1(n1);
  std::vector<int> vec2(n2);

  for(int i=0;i<n1;i++){
      vec1[i]=vec[left+i];
  }
  for(int i=0;i<n2;i++){
      vec2[i]=vec[mid+1+i];
  }

  int i=0,j=0,k=left;
  while(i<n1 && j<n2){
    if(vec1[i]<vec2[j]){
      vec[k++]=vec1[i++];
    }
    else if(vec1[i]>=vec2[j]){
      vec[k++]=vec2[j++];
    }
  }

  while(i<n1){
    vec[k++]=vec1[i++];
  }
  while(j<n2){
    vec[k++]=vec2[j++];
  }
}

void MergeSort(std::vector<int>& vec,int left,int right){

  if(left>=right) return;
  int mid=left+(right-left)/2;

  MergeSort(vec,left,mid);
  MergeSort(vec,mid+1,right);
  
  Merge(vec,left,mid,right);
}

void mergeSort(std::vector<int>& vec){

  MergeSort(vec,0,vec.size()-1);
}

//堆排序 不稳定 不需要额外空间
void Heap(std::vector<int>& vec,int n,int root){
  
  int left= 2*root+1;
  int right= 2*root+2;
  int larget = root;

  if(left<n && vec[left]>vec[larget]){
    larget=left;
  }
  if(right<n && vec[right]>vec[larget]){
    larget=right;
  }

  if(larget!=root){

    std::swap(vec[larget],vec[root]);
    Heap(vec,n,larget);
  }
} 


void heapSort(std::vector<int>& vec){

  int n=vec.size();
  //构建大根堆
  for(int i=n/2-1;i>=0;i--){
    Heap(vec,n,i);
  }

  for(int i=n-1;i>0;i--){
    std::swap(vec[0],vec[i]);
    Heap(vec,i,0);
  }
}

//计数排序 非比较型排序 复杂度为o(n)
void countSort(std::vector<int>& vec){

  int n=vec.size();

  int maxV=*std::max_element(vec.begin(),vec.end()); 
  int minV=*std::min_element(vec.begin(),vec.end());
  
  int range = maxV - minV + 1;

  std::vector<int> count(range);

  for(int num:vec){
    count[num-minV]++;
  }

  for(int i=1;i<range;i++){
    count[i]+=count[i-1];
  } 

  std::vector<int> ret(n);

  for(int i=vec.size()-1;i>=0;i--){
    ret[count[vec[i]-minV]-1]=vec[i];
    count[vec[i]-minV]--;
  }

  for(int i=0;i<vec.size();i++){
    vec[i]=ret[i];
  }
}

//桶排序
void bucketSort(std::vector<int>& vec){
  
  if(vec.empty()) return;
  int n=vec.size();

  int maxV=*std::max_element(vec.begin(),vec.end());
  int minV=*std::min_element(vec.begin(),vec.end());

  int bucketCount=vec.size();
  int range=(maxV-minV)/bucketCount;

  std::vector<std::vector<int>> buckets(bucketCount);

  for(auto& value:vec){
    int index=(value-minV)/range;
    if(index>=bucketCount){
        index=bucketCount-1;
    }
    buckets[index].push_back(value);
  }

  for(auto& v:buckets){
    std::sort(v.begin(),v.end());
  }

  int index=0;

  for(auto& v:buckets){
    for(auto& a:v){
      vec[index++]=a;
    }
  }
  
}

//基数排序
int getMaxDigist(std::vector<int>& vec){
  int maxV=*std::max_element(vec.begin(),vec.end());
  int digist=0;
  while(maxV!=0){
    maxV /=10;
    digist++;
  }
  return digist;
  
}

void radixSort(std::vector<int>& vec){
  
  int maxDigist=getMaxDigist(vec);
  int base=10;

  for(int i=1;maxDigist>0;i*=10,maxDigist--){
    std::vector<int> ret(vec.size());
    std::vector<int> count(base,0);

    for(auto num:vec){
      int digist=(num/i)%base;
      count[digist]++;
    }

    for(int j=1;j<base;j++){
     count[j]+=count[j-1]; 
    }

    for(int j=vec.size()-1;j>=0;j--){
      int digist=(vec[j]/i)%10;
      ret[count[digist]-1]=vec[j];
      count[digist]--;
    }

    for(int i=0;i<vec.size();i++){
      vec[i]=ret[i];
    }
  }
  
}
