package com.example.chess;

import android.content.Context;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.media.Image;
import android.os.Handler;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import org.w3c.dom.Text;

import java.net.Socket;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

public class BorderAdapter extends BaseAdapter {
    List<Integer> IDS;
    List<Integer> IMAGES;
    List<Integer> BACKGROUNDS;
    String username, type;
    ImageView last_clicked;
    TextView log;
    Boolean youWhite;
    Integer last_background;
    int last = -1, pred_position = -1;
    static int count_updates = 0;
    static boolean isRunning = false;
    static boolean hasChanged = false;
    static boolean update_started = false;
    Context context;
    private static LayoutInflater inflater=null;
    public BorderAdapter(Play activity, List<Integer> ids, List<Integer> images, List<Integer> colors, String user, String typ, TextView l, Boolean yw) {
        IDS=ids;
        IMAGES=images;
        BACKGROUNDS=colors;
        username=user;
        type=typ;
        log=l;
        youWhite = yw;
        context=activity;
        count_updates = 0;
        isRunning = false;
        hasChanged = false;
        update_started = false;
        inflater = ( LayoutInflater )context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);

        if(type.equals("ai") || type.equals("player")) {
            startScheduler(false);
        }
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

    String toStep(int fr, int to) {
        if(!youWhite) {
            fr = 63-fr;
            to = 63-to;
        }
        String res = "";
        res += String.valueOf(fr/8)+",";
        res += String.valueOf(fr%8)+",";
        res += String.valueOf(to/8)+",";
        res += String.valueOf(to%8);
        return res;
    }

    public void startScheduler(boolean firstUpdate) {
        if(!isRunning) {
            isRunning = true;
            Handler handler = new Handler();
            Runnable runnable = new Runnable() {
                public void run() {
                    if(firstUpdate) {
                        handler.post(new Runnable() {
                            public void run() {
                                updateBoardUI();
                            }
                        });
                    }
                    while (!hasChanged && count_updates <= 20) {
                        try {
                            Thread.sleep(150);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                        handler.post(new Runnable() {
                            public void run() {
                                hasChanged = updateBoardUI();
                            }
                        });
                        count_updates++;
                    }
                    isRunning = false;
                    count_updates = 0;
                }
            };
            new Thread(runnable).start();
        }
    }

    int toPiece(char ch) {
        switch (ch) {
            case ' ': return R.mipmap.empty_foreground;
            case '♙': return R.mipmap.white_pawn_foreground;
            case '♖': return R.mipmap.white_rook_foreground;
            case '♘': return R.mipmap.white_knight_foreground;
            case '♗': return R.mipmap.white_bishop_foreground;
            case '♕': return R.mipmap.white_queen_foreground;
            case '♔': return R.mipmap.white_king_foreground;
            case '♟': return R.mipmap.black_pawn_foreground;
            case '♜': return R.mipmap.black_rook_foreground;
            case '♞': return R.mipmap.black_knight_foreground;
            case '♝': return R.mipmap.black_bishop_foreground;
            case '♛': return R.mipmap.black_queen_foreground;
            case '♚': return R.mipmap.black_king_foreground;
        }
        return R.mipmap.empty_foreground;
    }

    boolean updateBoardUI() {
        try {
            if(!update_started) {
                update_started = true;
                boolean is_changed = false;
                SocketHandler soc = new SocketHandler();
                soc.execute("get_pos|" + username + "|" + type, "true");
                String pos = soc.get(150, TimeUnit.MILLISECONDS);
                if (!youWhite) pos = new StringBuilder(pos).reverse().toString();
                List<Integer> temp = new ArrayList<Integer>(IMAGES);
                IMAGES.clear();
                for (int i = 0; i < pos.length(); ++i) {
                    int piece = toPiece(pos.charAt(i));
                    if (piece != temp.get(i)) is_changed = true;
                    IMAGES.add(piece);
                }
                notifyDataSetChanged();
                update_started = false;
                return is_changed;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return true;
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
        //holder.img.setBackgroundColor(Color.parseColor("#d5bdbd"));

        rowView.setOnClickListener(new OnClickListener() {

            @Override
            public void onClick(View v) {
                int cur = IDS.get(position);
                if(last == -1) {
                    last_background = BACKGROUNDS.get(position);
                    holder.img.setBackgroundColor(Color.parseColor("#d5bdbd"));
                    BACKGROUNDS.set(position, Color.parseColor("#d5bdbd"));
                    pred_position = position;
                    last = cur;
                    last_clicked = holder.img;
                }
                else if(last != cur) {
                    holder.img.setBackgroundColor(Color.parseColor("#d5bdbd"));
                    BACKGROUNDS.set(pred_position, last_background);
                    pred_position = position;
                    last_clicked.setBackgroundColor(last_background);
                    last_background = BACKGROUNDS.get(position);
                    BACKGROUNDS.set(position, Color.parseColor("#d5bdbd"));

                    try {
                        SocketHandler soc = new SocketHandler();
                        soc.execute("do_step|" + username + "|" + type + "|" + toStep(last, cur), "true");
                        String result = soc.get(200, TimeUnit.MILLISECONDS);

                        if (!result.equals("incorrect")) {

                            if (result.equals("draw")) {
                                log.setText("Ничья");
                            } else if (result.equals("white")) {
                                log.setText("Победили белые");
                            } else if (result.equals("black")) {
                                log.setText("Победили чёрные");
                            }
                        }

                        if (!result.equals("incorrect")) {
                            if(type.equals("ai") || type.equals("player")) {
                                startScheduler(true);
                            }
                            else {
                                updateBoardUI();
                            }
                        }
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    } catch (ExecutionException e) {
                        e.printStackTrace();
                    } catch (TimeoutException e) {
                        e.printStackTrace();
                    }
                    last = cur;
                    last_clicked = holder.img;
                }
            }
        });

        return rowView;
    }

} 