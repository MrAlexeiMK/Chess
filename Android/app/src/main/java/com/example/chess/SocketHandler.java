package com.example.chess;

import android.app.PendingIntent;
import android.app.Service;
import android.content.Intent;
import android.os.IBinder;

import java.io.InputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class SocketHandler extends Service {
    ExecutorService es;
    private static PrintWriter sout;

    public void onCreate() {
        es = Executors.newFixedThreadPool(1);
        super.onCreate();
    }

    public static synchronized PrintWriter getPrintWriter() {
        return sout;
    }

    public void onDestroy() {
        super.onDestroy();
        new Thread(new Runnable() {
            @Override
            public void run() {
                sout.print("stop");
                sout.flush();
            }
        }).start();
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    public int onStartCommand(Intent intent, int flags, int startId) {
        String nickname = intent.getStringExtra("nickname");
        String type = intent.getStringExtra("type");
        PendingIntent pi = intent.getParcelableExtra("pending");
        Connect con = new Connect(nickname, type, startId, pi);
        es.execute(con);
        return super.onStartCommand(intent, flags, startId);
    }

    public static void sendMessage(String msg) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                sout.print(msg);
                sout.flush();
            }
        }).start();
    }

    class Connect implements Runnable {
        String nickname;
        String type;
        int startId;
        PendingIntent pi;
        public Connect(String nickname, String type, int startId, PendingIntent pi) {
            this.nickname = nickname;
            this.type = type;
            this.startId = startId;
            this.pi = pi;
        }

        public void run() {
            while (true) {
                try {
                    Socket soc = new Socket("127.0.0.1", 1234);
                    sout = new PrintWriter(soc.getOutputStream(), false);
                    sout.print(nickname+"|me|white");
                    sout.flush();
                    pi.send(MainActivity.STATUS_CONNECTED);

                    InputStream stream = soc.getInputStream();
                    String data;
                    byte[] buf = new byte[1024];
                    while (true) {
                        int count = stream.read(buf, 0, buf.length);
                        if (count > 0) {
                            data = new String(buf, 0, count);
                            String[] arr = data.split("|");
                            String board = arr[0];
                            String status = arr[1];
                            Intent intent;
                            intent = new Intent().putExtra("pos", board);
                            intent = new Intent().putExtra("status", status);
                            pi.send(SocketHandler.this, MainActivity.STATUS_GET_DATA, intent);
                        }
                    }
                } catch (Exception e) {
                    try {
                        TimeUnit.SECONDS.sleep(1);
                    } catch (InterruptedException e1) {
                        e1.printStackTrace();
                    }
                }
            }
        }

        void stop() {
            stopSelf(startId);
        }
    }
}
