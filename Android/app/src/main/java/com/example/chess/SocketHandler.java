package com.example.chess;

import android.os.AsyncTask;

import java.io.InputStream;
import java.io.PrintWriter;
import java.net.Socket;

public class SocketHandler extends AsyncTask<String, Void, String> {
    @Override
    protected void onPreExecute() {
        super.onPreExecute();
    }

    @Override
    protected String doInBackground(String... params) {
        try {
            String message = params[0];
            String get_data = params[1];
            Socket socket = new Socket("192.168.43.39", 1234);
            PrintWriter scout = new PrintWriter(socket.getOutputStream(), false);
            scout.print(message);
            scout.flush();

            if (get_data == "true") {
                InputStream stream = socket.getInputStream();
                String data;
                byte[] buf = new byte[1024];
                int count = stream.read(buf, 0, buf.length);
                if (count > 0) {
                    data = new String(buf, 0, count);
                    return data;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return "incorrect";
    }

    @Override
    protected void onPostExecute(String result) {
        super.onPostExecute(result);
    }
}