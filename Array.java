public class Array {

    private int[] data;
    private int size;

    public Array(int capacity){
        data=new int[capacity];
        size=0;

    }
    public Array(){
        this(10);
    }

    public getSize(){
        return size ;
    }

    public int getCapacity(){
        return data.length;
    }
     public boolean isEmpty(){
        return size==0;
     }

     //添加元素
     public void addLast(int e){

        if(size==data.length)
            throw new IllegalArgumentException("Add last failed.Array is full.");

        data[size]=e;
        size++;
     }

     //向指定位置(index位置）添加元素
    public void add(int index,int e){

        if(size==data.length)
            throw new IllegalArgumentException("Add last failed.Array is full.");

        if (index<0 || index>size)
            throw new IllegalArgumentException("Add last failed.Array is full.");

        for(int i =size-1;i>=index;i--)
            data[i+1]=data[i];

        data[index]=e;
        size++;
    }
    //获取index位置上元素
    int get(int index){
        if (index<0 || index>size)
            throw new IllegalArgumentException("Add last failed.Array is full.");
        return data[index];
    }

    //修改index位置上元素为e
    void set(int index,int e){
        if (index<0 || index>size)
            throw new IllegalArgumentException("Add last failed.Array is full.");
        data[index]=e

    }

    @Override
    public String toString(){

        StringBuilder res=new StringBuilder();
        res.append(String.format("Array:size=%d,capacity=%d\n",size,data.length));
        res.append('[');
        for (int i =0;i<size;i++) {
            res.append(data[i]);
            if (i != size - 1)
                res.append(","):
        }
        res.append(']');
        return res.toString();

    }
}
