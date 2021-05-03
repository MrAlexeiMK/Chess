package com.example.chess;

import android.app.PendingIntent;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.GridView;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class Play extends AppCompatActivity {
    public final static int STATUS_CONNECTED = 100;
    public final static int STATUS_DISCONNECTED = 101;
    public final static int STATUS_GET_DATA = 102;
    public static List<Integer> ids;
    public static List<Integer> images;
    public static List<Integer> backgrounds;
    TextView log2;
    String username, type;
    boolean youWhite;
    GridView gv;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_play);
        Intent intent = getIntent();
        log2 = (TextView)findViewById(R.id.log2);
        username = ""+intent.getStringExtra("username");
        type = ""+intent.getStringExtra("type");

        ids = new ArrayList<Integer>();
        images = new ArrayList<Integer>();
        backgrounds = new ArrayList<Integer>();
        youWhite = true;

        initGrid();
        createGrid();

        startConnect();
    }

    public void initGrid() {
        images.add(R.mipmap.black_rook_foreground);
        images.add(R.mipmap.black_knight_foreground);
        images.add(R.mipmap.black_bishop_foreground);
        images.add(R.mipmap.black_queen_foreground);
        images.add(R.mipmap.black_king_foreground);
        images.add(R.mipmap.black_bishop_foreground);
        images.add(R.mipmap.black_knight_foreground);
        images.add(R.mipmap.black_rook_foreground);
        for(int i = 0; i < 8; ++i) images.add(R.mipmap.black_pawn_foreground);
        for(int i = 0; i < 32; ++i) images.add(R.mipmap.empty_foreground);
        for(int i = 0; i < 8; ++i) images.add(R.mipmap.white_pawn_foreground);
        images.add(R.mipmap.white_rook_foreground);
        images.add(R.mipmap.white_knight_foreground);
        images.add(R.mipmap.white_bishop_foreground);
        images.add(R.mipmap.white_queen_foreground);
        images.add(R.mipmap.white_king_foreground);
        images.add(R.mipmap.white_bishop_foreground);
        images.add(R.mipmap.white_knight_foreground);
        images.add(R.mipmap.white_rook_foreground);

        if(type.equals("ai")) {
            Random ran = new Random(System.currentTimeMillis());
            double randomNum = ran.nextDouble();
            if(randomNum < 0.5) {
                Collections.reverse(images);
                youWhite = false;
            }
        }
    }

    public void createGrid() {
        gv=(GridView) findViewById(R.id.board);
        int j = 1;
        if(!youWhite) j = 0;
        for(int i = 0; i < 64; ++i) {
            ids.add(i);
            if(i%8 == 0) --j;
            if(j%2 == 0) {
                backgrounds.add(Color.parseColor("#eeeed2"));
            }
            else backgrounds.add(Color.parseColor("#a0c030"));
            ++j;
        }
        gv.setAdapter(new BorderAdapter(this, ids, images, backgrounds, username, type));
    }

    public void back(View v) {
        if(v.getId() == R.id.menu) {
            stopConnect();
            finish();
        }
    }

    public void startConnect() {
        PendingIntent pi;
        Intent intent;
        Intent www = new Intent();
        pi = createPendingResult(1, www, 0);
        intent = new Intent(this, SocketHandler.class).putExtra("nickname", username).putExtra("type", type)
                .putExtra("pending", pi);
        startService(intent);
    }

    public void stopConnect() {
        stopService(new Intent(this, SocketHandler.class));
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        switch (resultCode) {
            case STATUS_CONNECTED:
                log2.setText("Успешное подключение");
                break;
            case STATUS_DISCONNECTED:
                log2.setText("Не удалось подключиться");
                break;
            case STATUS_GET_DATA:
                String pos = data.getStringExtra("pos");
                String status = data.getStringExtra("status");
                break;
        }
    }
}
