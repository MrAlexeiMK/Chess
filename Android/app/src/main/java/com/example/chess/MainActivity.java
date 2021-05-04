package com.example.chess;

import androidx.appcompat.app.AppCompatActivity;

import android.app.PendingIntent;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    TextView info, username, log;
    Button play, play_ai;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        info = (TextView)findViewById(R.id.info);
        username = (TextView) findViewById(R.id.username);
        log = (TextView) findViewById(R.id.log);
        play = (Button)findViewById(R.id.play);
        play_ai = (Button)findViewById(R.id.play_ai);
    }

    String delSymbols(String s, String syms) {
        String res = "";
        for(int i = 0; i < s.length(); ++i) {
            boolean ch = true;
            for(int j = 0; j < syms.length(); ++j) {
                if(s.charAt(i) == syms.charAt(j)) {
                    ch = false;
                    break;
                }
            }
            if(ch) res += s.charAt(i);
        }
        return res;
    }

    public void playBoth(View v) {
        username.setText(delSymbols(username.getText().toString(), "|"));
        if(!username.getText().toString().isEmpty()) {
            Intent intent = new Intent(this, Play.class).putExtra("username", username.getText().toString()).putExtra("type", "me");
            startActivity(intent);
        }
    }

    public void playWithAI(View v) {
        username.setText(delSymbols(username.getText().toString(), "|"));
        if(!username.getText().toString().isEmpty()) {
            Intent intent = new Intent(this, Play.class).putExtra("username", username.getText().toString()).putExtra("type", "ai");
            startActivity(intent);
        }
    }
}