public class LinearSearch {

    private LinearSearch(){}

    public static<E> int search(E[] data,E target){

        for(int i =0;i<data.length;i++)
             if(data[i].equals(target))
                 return i;

        return -1;

    }

    public static void main(String[] args){

        int n=100000;
        Integer[] data=ArrayGenertaor.generateOrderedArray(n);

        long startTime=System.nanoTime();
        LinearSearch.search(data,n);
        long endTime=System.nanoTime();

        double time=(endTime -startTime)/1000000000.0;
        System.out.println(time+'s');
    }
}
