#include "engine.h"

void UpdateMenuPosition(struct nk_rect *menu,
    int x, int y, int w, int h)
{
    menu->x = x; menu->y = y;
    menu->w = w; menu->h = h;

    matrix_width = screen_width - screen_gaps * 2;
}

void SetFont(struct nk_context *nk_ctx,
    const char *font_path, const unsigned char font_size)
{
    struct nk_font_atlas *atlas;
    nk_sdl_font_stash_begin(&atlas);
    struct nk_font *font = nk_font_atlas_add_from_file(
        atlas, font_path, font_size, 0);
    nk_sdl_font_stash_end();
    nk_style_set_font(nk_ctx, &font->handle);
}

void SetMenuColor(struct nk_context *nk_ctx)
{
    struct nk_color table[NK_COLOR_COUNT];
    table[NK_COLOR_WINDOW] = nk_rgba(60, 60, 60, 0);
    table[NK_COLOR_TEXT] = nk_rgba(180, 180, 180, 255);
    nk_style_from_table(nk_ctx, table);
}

void Intro(SDL_Window *window, struct nk_context* nk_ctx)
{
    if (screen_width >= screen_height)
        screen_gaps = screen_width;
    else if (screen_width < screen_height)
        screen_gaps = screen_height;

    struct nk_color table[NK_COLOR_COUNT];
    table[NK_COLOR_WINDOW] = nk_rgba(60, 60, 60, 25);
    table[NK_COLOR_TEXT] = nk_rgba(180, 180, 180, 255);
    nk_style_from_table(nk_ctx, table);

    while (screen_gaps > default_screen_gaps)
    {
        GetEvent(window, nk_ctx);
        screen_gaps -= gaps_step;
        UpdateMenuPosition(&main_menu, main_menu_gaps);
        Render(window, nk_ctx);
    }
}

int view_flag = 0;

nk_bool status = nk_false;

void Canvas(SDL_Window *window, struct nk_context* nk_ctx)
{
   if (nk_begin(nk_ctx, "", main_menu,
            NK_WINDOW_BORDER
            | NK_WINDOW_NO_SCROLLBAR
            | NK_WINDOW_BACKGROUND)) 
    {
        nk_layout_row_dynamic(nk_ctx, (screen_height-screen_gaps*2.0)/5.0, 1);
        nk_spacing(nk_ctx, 2);
        nk_label(nk_ctx, "Hello World!", NK_TEXT_CENTERED);
        if (nk_checkbox_label(nk_ctx, "View", &status)) view_flag = !view_flag;
    }
    nk_end(nk_ctx);
}

void ViewMatrix(struct nk_context * nk_ctx, struct nk_rect * menu)
{
    if (menu->w < matrix_width) menu->w += gaps_step;
    else if (menu->w > matrix_width) menu->w -= gaps_step;

    nk_flags flag = NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR;
    if (view_flag) flag |= NK_WINDOW_CLOSED;
    if (nk_begin(nk_ctx, "Matrix Canvas", *menu, flag))
    {
        nk_layout_row_static(nk_ctx, 28, 80, 10);
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                char buffer[10];
                sprintf(buffer, "%5.4f ", perf_memb[i][j]);
                nk_text(nk_ctx, buffer, 6, NK_TEXT_CENTERED);
            }
        }
    }
    nk_end(nk_ctx);
}

void DataEditor(struct nk_context * nk_ctx, struct nk_rect * region,
    float data[furnace_count][furnace_count])
{

    static int data_len[furnace_count][furnace_count];
    static char data_buf[furnace_count][furnace_count][50];

    static int init = 1;
    if (init) {
        for (int i = 0; i < furnace_count; i++)
            for (int j = 0; j < furnace_count; j++)
                data_len[i][j] = sprintf(data_buf[i][j], "%4.3f", data[i][j]);
        init = 0;
    }

    static int view_flag = 1;
    nk_flags nk_flags = \
        NK_WINDOW_BORDER
        | NK_WINDOW_TITLE
        | NK_WINDOW_NO_SCROLLBAR
        ;
    if (!view_flag) nk_flags |= NK_WINDOW_CLOSED;

    if (nk_begin(nk_ctx, "Data Editor", *region, nk_flags)) {
        nk_layout_row_static(nk_ctx, 35, 50, 10);
        for (int i = 0; i < furnace_count; i++)
            for (int j = 0; j < furnace_count; j++) {
                nk_edit_string(nk_ctx, NK_EDIT_SIMPLE,
                    data_buf[i][j], &data_len[i][j], 10, nk_filter_float);
                data_buf[i][j][data_len[i][j]] = '\0';
            }
    } nk_end(nk_ctx);
}

