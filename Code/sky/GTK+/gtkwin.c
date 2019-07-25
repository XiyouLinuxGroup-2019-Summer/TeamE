#include <stdio.h>
#include <gtk/gtk.h>
void hello(GtkWidget *widget,gpointer *data)
{
    g_print("button clicked and data = %s\n",(char*)data);
}

void destroy(GtkWidget *widget,gpointer *data)
{
    gtk_main_quit();
}
int main(int argc,char **argv)
{
    //定义指向控件的指针
    GtkWidget *window;
    GtkWidget *button;

    //初始化图形显示环境
    gtk_init(&argc,&argv);

    //创建窗口，设置当关闭窗口时候，要执行回调函数
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(GTK_OBJECT(window),"destory",GTK_SIGNAL_FUNC(destroy),NULL);

    //设置窗口属性
    gtk_container_border_width(GTK_CONTAINER(window),200);

    //创建按钮，并设置当单击按钮时，叙执行的函数
    button = gtk_button_new_with_label("Hello World");
    g_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(hello),"I am from button");

    //将按钮加入到窗口中
    gtk_container_add(GTK_CONTAINER(window),button);

    //显示按钮和窗口
    gtk_widget_show(button);
    gtk_widget_show(window);

    //进入消息处理函数
    gtk_main();
    return 0;
}

