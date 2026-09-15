public class LinkedList<E> {

    private class Node {
        public E e;
        public Node next;

        public Node(E e, Node next) {
            this.e = e;
            this.next = next;
        }

        public Node(E e) {
            this(e, null);
        }

        public Node() {
            this(null, null);
        }

        @Override
        public String toString() {
            return e.toString();
        }

    }

    private Node dummyHead;
    private int size;

    public LinkedList(){
        dummyHead=new Node(null,null);
        size=0;
    }

    //获取个数
    public int getSize(){
        return size;
    }

    public boolean isEmpty(){
        return size==0;
    }

    //在链表的index位置添加元素e
    public void add(int index,E e){
        if(index<0||index>size)
            throw new IllegalArgumentException("add failed ");


            Node prev=dummyHead;
            for(int i=0;i<index;i++)//找到index前一个节点
                prev=prev.next;

            Node node=new Node(e);
            node.next=prev.next;
            prev.next=node;

            size++;
        }

    //在链表头添加元素
    public void addFirst(E e){
        //Node node=new Node(e);
        //node.next=head;
        //head=node;
        add(0,e);
    }

    //获得第index元素
    public E get(int index){
        if(index<0||index>=size)
            throw new IllegalArgumentException("get failed.illegal index");

        Node cur=dummyHead.next;
        for(int i=0;i<index;i++)
            cur=cur.next;
        return cur.e;
    }

    //获得链表第一个元素
    public E getFirst(){
        return get(0);
    }

    public E getLast(){
        return get(size-1);
    }

    //修改链表的index元素
    public void set(int index,E e) {
        if (index < 0 || index >= size)
            throw new IllegalArgumentException("set failed.illegal index");
        Node cur = dummyHead.next;
        for (int i = 0; i < index; i++)
            cur = cur.next;
        cur.e = e;
    }
    //查找是否有元素e
    public boolean contains(E e) {
        Node cur = dummyHead.next;
        while (cur != null) {
            if (cur.e.equals(e))
                return true;
            cur = cur.next;
        }
        return false;
    }

    //链表中删除index元素,返回删除的元素是谁
    public E remove(int index){
        if (index < 0 || index >= size)
            throw new IllegalArgumentException("remove failed.illegal index");

        Node prev=dummyHead;
        for(int i=0;i<index;i++)
            prev=prev.next;

        Node retNode=prev.next;
        prev.next=retNode.next;
        retNode.next=null;
        size--;

        return retNode.e;
    }

    public E removeFirst(){
        return remove(0);
    }

    public E removeLast(){
        return remove(size-1);
    }



    @Override

    public String toString() {
        StringBuilder res = new StringBuilder();
        Node cur = dummyHead.next;
        while (cur != null) {
            res.append(cur + "->");
            cur = cur.next;
        }
        res.append("NULL");
        return res.toString();
    }



}

