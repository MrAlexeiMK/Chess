package com.example.chess;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
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
    public TextView log;
    String username, type;
    boolean youWhite;
    GridView gv;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_play);
        Intent intent = getIntent();
        log = (TextView)findViewById(R.id.info_play);
        username = ""+intent.getStringExtra("username");
        type = ""+intent.getStringExtra("type");

        ids = new ArrayList<Integer>();
        images = new ArrayList<Integer>();
        backgrounds = new ArrayList<Integer>();
        youWhite = true;

        initGrid();
        addUser();
        createGrid();
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
        gv.setAdapter(new BorderAdapter(this, ids, images, backgrounds, username, type, log, youWhite));
    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();
        delUser();
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        BorderAdapter.count_updates = 21;
        delUser();
    }

    @Override
    public void onStop() {
        super.onStop();
        delUser();
    }

    public void back(View v) {
        if(v.getId() == R.id.menu) {
            delUser();
            finish();
        }
    }

    public void addUser() {
        SocketHandler soc = new SocketHandler();
        String you_white_str = "black";
        if(youWhite) you_white_str = "white";
        soc.execute("user_add|"+username+"|"+type+"|"+you_white_str, "false");
    }

    public void delUser() {
        SocketHandler soc = new SocketHandler();
        soc.execute("user_remove|"+username+"|"+type, "false");
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        switch (resultCode) {
            case STATUS_CONNECTED:
                log.setText("Успешное подключение");
                break;
            case STATUS_DISCONNECTED:
                log.setText("Не удалось подключиться");
                break;
            case STATUS_GET_DATA:

                break;
        }
    }
}
