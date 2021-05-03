package com.example.chess;

import android.content.Context;
import android.graphics.Color;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.Toast;

import java.net.Socket;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class BorderAdapter extends BaseAdapter {
    List<Integer> IDS;
    List<Integer> IMAGES;
    List<Integer> BACKGROUNDS;
    String username, type;
    HashMap<ImageView, Integer> clicked = new HashMap<ImageView, Integer>();
    int last = -1;

    Context context;
    private static LayoutInflater inflater=null;
    public BorderAdapter(Play activity, List<Integer> ids, List<Integer> images, List<Integer> colors, String user, String typ) {
        IDS=ids;
        IMAGES=images;
        BACKGROUNDS=colors;
        username=user;
        type=typ;
        context=activity;
        inflater = ( LayoutInflater )context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
    }

    @Override
    public int getCount() {
        return IDS.size();
    }

    @Override
    public Object getItem(int position) {
        return position;
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    public class Holder {
        ImageView img;
    }
    @Override
    public View getView(final int position, View convertView, ViewGroup parent) {
        Holder holder = new Holder();
        View rowView;

        rowView = inflater.inflate(R.layout.activity_grid, null);
        holder.img=(ImageView) rowView.findViewById(R.id.piece);

        holder.img.setImageResource(IMAGES.get(position));
        holder.img.setBackgroundColor(BACKGROUNDS.get(position));

        rowView.setOnClickListener(new OnClickListener() {

            @Override
            public void onClick(View v) {
                //IDS.get(position)
                //Toast.makeText(context, "You Clicked "+IDS.get(position), Toast.LENGTH_LONG).show();
                int cur = IDS.get(position);
                SocketHandler.sendMessage(username+"|"+type+"|1,1,2,2");
                if(last == -1) {
                    clicked.put(holder.img, BACKGROUNDS.get(position));
                    holder.img.setBackgroundColor(Color.parseColor("#d5bdbd"));
                    last = cur;
                }
                else if(last != cur) {
                    holder.img.setBackgroundColor(Color.parseColor("#d5bdbd"));
                    last = cur;
                    for(ImageView im : clicked.keySet()) {
                        im.setBackgroundColor(clicked.get(im));
                    }
                    clicked.clear();
                    clicked.put(holder.img, BACKGROUNDS.get(position));
                }
            }
        });

        return rowView;
    }

} 