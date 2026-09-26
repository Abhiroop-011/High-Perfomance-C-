// [1 2 3 4 ] -> [8] -> [ 1 2 3 4 6 7 8 9] -> [8] -> [8\]
// std::vector .. GOES BEYOND 10 ... 20 COPY 10 ELEMNT DELETE 10
// std::list [prev data next] - new DLL()
//
//
//
//
// stack
// MAIN
// 4 MB
// THREAD1
// 2MB
// THREAD 2
// 2 MB
// ....
// STACK 1KB
// heap
// MAIN ... STACK
// VOID F(){
//  RETURN F();
// }
// VOID DFS(){
// RETURN X;
// }
//   bid ask
//   1. reliance
//   1000 100
// 998 998.5
//
//   1000 events
//  QUEUE 1000 ENTRIES
//  IF QUEUE IS FULLL ???
//  [5][6][7][4]
//  // 5 IS THE LATEST
//  RING BUFFER .... CIRCULE QUEUE
template <typename T> class SPSC {
public:
  SPSC() = default;
  SPSC(size_t size): mSize(size){
    mData = static_cast<T*>(::operator new(sizeof(T)*size));
  }
  SPSC(const SPSC<T>&) = delete;
  SPSC(SPSC&&) = delete;
  SPSC& opertor=(const SPSC<T>&) = delete;
  ~SPSC(){
    delete mData;
  }
  bool push(T val) {
    if(size() == mSize)
      return false;

    mData[mPushIdx] = val;
    mPushIdx = (mPushIdx+1)%mSize;
    return true;
  }
  T pop() {
    if(empty())
      throw;
    T val = mData[mPopIdx];
    mPopIdx = (mPopIdx+1)%mSize;
    return val;
  }

private:
  size_t size(){
    return mPushIdx - mPopIdx;
  }
  bool empty(){
    return mPushIdx == mPopIdx;
  }
  T *mData{nullptr};
  size_t mPushIdx {0u};
  size_t mPopIdx  {0u};
};
void producer() {}

void consumer() {}
int main() {
  SPSC<int> q;
  std::thread p(producer);
  std::thread c(consumer);;
  p.join();
  c.join();
}
