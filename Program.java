//import java.sql.Date;

import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;

class db {
    int id_system;
    Date date_block;

    db(int x, Date y) {
        id_system = x;
        date_block = y;
    }
}

// all this function 'main' will be executing again and again
public class Program {
    public static void main(String[] args) {
        int elements = 7; // how many lines

        create_db cdb = new create_db();
        db[] data_recipient_ban = cdb.fill_db(elements);

        Date time = new Date();

//        System.out.println("now");
//        System.out.println(time.getTime());
//        System.out.println("dif");
//        System.out.println(time.getTime() - data_recipient_ban[0].date_block.getTime());
        System.out.println("before");
        cdb.print_db(data_recipient_ban, elements);
        System.out.println("after");
        data_recipient_ban = cdb.delete_db(data_recipient_ban, elements, time.getTime());
        cdb.print_db(data_recipient_ban, elements);
    }
}

class create_db {
    public db[] fill_db(int elems) {
        db[] arr = new db[elems];
        Date tmp;

        for (int i = 0; i < elems; i++) {
            // find out the date and put into 'tmp' instead of hand-making
            GregorianCalendar calendar = new GregorianCalendar(2022, 7, 13);
            calendar.set(Calendar.HOUR, 21);
            calendar.set(Calendar.MINUTE, 17);
            calendar.set(Calendar.SECOND, 12);

            tmp = calendar.getTime();
            arr[i] = new db(132, tmp);
        }

        return arr;
    }

    public void print_db(db[] arr, int elems) {
        for(int i = 0; i < elems; i++) {
            try{
                System.out.println(arr[i].date_block);
            } catch(NullPointerException ex) {
                break;
            } catch(ArrayIndexOutOfBoundsException ex) {
                break;
            }
        }
    }

    public db[] delete_db(db[] arr, int elems, long time) {
        long tmp;
        int count_deletes = 0;

        for (int i = 0; i < elems; i++) {
            tmp = arr[i].date_block.getTime();
            if (time - tmp > 3600000) {
                // delete line from bd
                // now another way
                count_deletes++;
                if (i < elems - count_deletes) {
                    arr[i] = arr[i + count_deletes];
                }
            } else {
                arr[i] = arr[i + count_deletes];
            }
        }

        // return new db, no realloc, so new array
        db[] new_arr = new db[elems - count_deletes];

        for (int i = 0; i < elems - count_deletes; i++) {
            new_arr[i] = arr[i];
        }

        return new_arr;
    }
}