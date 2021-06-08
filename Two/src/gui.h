void SetFont(struct nk_context *nk_ctx, 
    const char *font_path, const unsigned char font_size);
void SetMenuColor(struct nk_context *nk_ctx);

void UpdateMenuPosition(struct nk_rect *menu, int x, int y, int w, int h);

void Intro  (SDL_Window *, struct nk_context *);

void ViewMatr(struct nk_context * nk_ctx, struct nk_rect * region);

void InitDataLength(float data[furnace_count],
    char data_buf[furnace_count][20], int data_len[furnace_count]);
