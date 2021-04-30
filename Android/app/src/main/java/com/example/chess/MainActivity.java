package com.example.chess;

import androidx.appcompat.app.AppCompatActivity;

import android.app.PendingIntent;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    public final static int STATUS_CONNECTED = 100;
    public final static int STATUS_DISCONNECTED = 101;
    public final static int STATUS_GET_DATA = 102;
    TextView info, username;
    Button play, play_ai;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        info = (TextView)findViewById(R.id.info);
        username = (TextView) findViewById(R.id.username);
        play = (Button)findViewById(R.id.play);
        play_ai = (Button)findViewById(R.id.play_ai);
    }

    public void playBoth(View v) {
        if(username.getText() != "") {
            startConnect("me");
            Intent intent = new Intent(MainActivity.this, Play.class);
            intent.putExtra("type", "me");
            startActivity(intent);
        }
    }

    public void playWithAI(View v) {
        if(username.getText() != "") {
            startConnect("ai");
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        switch (resultCode) {
            case STATUS_CONNECTED:
                info.setText("Подключено");
                break;
            case STATUS_DISCONNECTED:
                info.setText("Подключение...");
                break;
            case STATUS_GET_DATA:
                String pos = data.getStringExtra("pos");
                String status = data.getStringExtra("status");
                break;
        }
    }

    public void startConnect(String type) {
        PendingIntent pi;
        Intent intent;
        Intent inten = new Intent();
        pi = createPendingResult(1, inten, 0);
        intent = new Intent(MainActivity.this, SocketHandler.class).putExtra("nickname", username.getText()).putExtra("type", type)
                .putExtra("pending", pi);
        startService(intent);
    }

    public void stopConnect() {
        stopService(new Intent(MainActivity.this, SocketHandler.class));
    }
}