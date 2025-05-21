1.	Thông tin Tác giả
Họ và tên: Nguyễn Trần Quang Tuyển
MSV: 24021670

2.	Giới thiệu Game (Tuyển VS SDL2)
Đây là một game bắn súng góc nhìn thứ 3 được xây dựng và phát triển qua thư viện SDL2. Game đưa bạn vào một thế giới, nơi mà thế giới con người đã bị tàn phá bởi các quái vật đến từ ngoài không gian. Chỉ còn bạn là người sống sót cuối cùng, hãy bước lên Robot và sống sót lâu nhất có thể.

3.Ngưỡng điểm tự đánh giá và những lý do để bảo vệ ngưỡng điểm trên
- Em tự đánh giá đây là một Game em đã rất đầu tư và tâm huyết, em đánh giá mình có thể nhận được mức điểm từ 9,5 – 10.
- Bảo vệ điểm:
Code sạch, dễ đọc, debug.

Chia thành các file: các class nhỏ chứa các chức năng riêng biệt.

Load Map: TileSet dựa trên một ma trân map bên ngoài(.dat).

Đồ họa: Hỗ trợ Load/Render texture (GUI, player,…), các hàm vẽ SDL2, xoay texture, Load/Render animation.

Xử lý sự kiện: bao gồm sự kiện chuột và bàn phím.

Xử lý va chạm: AABB Collision

Cơ chế tính điểm

Hệ thống nút setting: quit, replay, turn on/off music, sfx.

Hệ thống nâng cấp vô hạn: bao gồm 2 loại: Buff dựa trên kinh nghiệm và Boost dựa trên điểm cảm hứng( triển nghiệm Game sẽ nói)

Cơ chế Boss gồm 2 chiêu: Thả bom và dịch chuyển (có thể phát triển thêm)

Quản lý quái trên Vector: dễ truy nhập, xử lý các chức năng

4. Nguồn tham khảo
Ý tưởng Code, hỗ trợ
https://www.youtube.com/watch?v=q1WzniyeGTU&list=PLR7NDiX0QsfQQ2iFXsXepwH46wf3D4Y4C
https://www.youtube.com/watch?v=KsG6dJlLBDw
https://lazyfoo.net/tutorials/SDL/02_getting_an_image_on_the_screen/index.php

Assets(Images, Sprite)
https://craftpix.net/freebies/free-roguelike-shoot-em-up-pixel-art-game-kit/
(và một số ảnh trên mạng khác)

Mức độ sử dụng AI: đây là một công cụ đắc lực giúp em có thể kiểm soát các lỗi, hỗ trợ đưa ra giải pháp để thực tế hóa các ý tưởng của chính em, hỗ trợ debug một số lỗi khó giải quyết.





