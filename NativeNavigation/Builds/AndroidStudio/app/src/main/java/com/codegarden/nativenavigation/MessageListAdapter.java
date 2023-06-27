package com.codegarden.nativenavigation;

import androidx.drawerlayout.widget.DrawerLayout;
import androidx.recyclerview.widget.RecyclerView;

import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import java.util.List;

public class MessageListAdapter extends RecyclerView.Adapter<MessageListAdapter.MessageViewHolder>{

    static List<Message> messages;
    private static ClickListener clickListener;
    private static StringBuilder messageTitle;
    private static DrawerLayout drawerLayout;

    private JuceActivity ref;

    MessageListAdapter(JuceActivity activity, List<Message> messages, StringBuilder messageTitle, DrawerLayout drawerLayout){
        ref = activity;
        MessageListAdapter.messages = messages;
        MessageListAdapter.messageTitle = messageTitle;
        MessageListAdapter.drawerLayout = drawerLayout;
    }

    public void setOnItemClickListener(ClickListener clickListener) {
        this.clickListener = clickListener;
    }

    @Override
    public MessageViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.drawer_item, parent, false);
        MessageViewHolder messageViewHolder = new MessageViewHolder(ref, view);
        return messageViewHolder;
    }

    @Override
    public void onBindViewHolder(MessageViewHolder holder, int position) {
        holder.itemTitle.setText(messages.get(position).title);
    }

    @Override
    public int getItemCount() {
        if (messages != null) {
            return messages.size();
        }
        else {
            return 0;
        }
    }

    @Override
    public void onAttachedToRecyclerView(RecyclerView recyclerView) {
        super.onAttachedToRecyclerView(recyclerView);
    }

    public Message getItem(int position) {
        return messages.get(position);
    }

    public interface ClickListener {
        void onItemClick(int position, View view);
    }

    public static class MessageViewHolder extends RecyclerView.ViewHolder implements View
            .OnClickListener {

        TextView itemTitle;

        JuceActivity activityRef;

        MessageViewHolder(JuceActivity ref, View itemView) {
            super(itemView);

            itemTitle = (TextView)itemView.findViewById(android.R.id.text1);
            itemView.setOnClickListener(this);

            activityRef = ref;
        }

        @Override
        public void onClick(View view) {
            Log.d("MessageListAdapter", "row " + getAdapterPosition() + " clicked");
            activityRef.setMessage(messages.get(getAdapterPosition()).message);
            messageTitle.setLength(0);
            messageTitle.append(messages.get(getAdapterPosition()).title);
            drawerLayout.closeDrawers();
        }
    }
}
