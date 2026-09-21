ALTER TABLE products
ADD COLUMN IF NOT EXISTS image_url TEXT;

UPDATE products
SET
    name = 'AeroBook Pro 15',
    description = 'Slim performance laptop for study, coding and everyday productivity.',
    price_cents = 5500000,
    stock_qty = 20,
    category = 'Electronics',
    image_url = 'https://images.unsplash.com/photo-1496181133206-80ce9b88a853?auto=format&fit=crop&w=900&q=85'
WHERE id = 1;

INSERT INTO products
(seller_id, name, description, price_cents, stock_qty, category, image_url)
SELECT 4, v.name, v.description, v.price_cents, v.stock_qty, v.category, v.image_url
FROM (
    VALUES
    ('Pulse X1 Smartphone','OLED display smartphone with fast performance and long battery life.',2499000,20,'Electronics','https://images.unsplash.com/photo-1511707171634-5f897ff02aa9?auto=format&fit=crop&w=900&q=85'),
    ('EchoWave Headphones','Wireless over-ear headphones with immersive sound.',799900,25,'Electronics','https://images.unsplash.com/photo-1505740420928-5e560c06d30e?auto=format&fit=crop&w=900&q=85'),

    ('Stride Run Max','Cushioned running shoes for everyday training.',399900,35,'Fashion','https://images.unsplash.com/photo-1542291026-7eec264c27ff?auto=format&fit=crop&w=900&q=85'),
    ('Everyday Oversized Hoodie','Soft oversized hoodie with a relaxed streetwear fit.',199900,30,'Fashion','https://images.unsplash.com/photo-1551488831-00ddcb6c6bd3?auto=format&fit=crop&w=900&q=85'),
    ('Urban Daypack','Minimal backpack for college and travel.',149900,25,'Fashion','https://images.unsplash.com/photo-1553062407-98eeb64c6a62?auto=format&fit=crop&w=900&q=85'),

    ('Glow Vitamin C Serum','Lightweight serum for a fresh daily skincare routine.',129900,40,'Beauty','https://images.unsplash.com/photo-1522335789203-aabd1fc54bc9?auto=format&fit=crop&w=900&q=85'),
    ('Velvet Bloom Perfume','Elegant floral and woody fragrance.',189900,20,'Beauty','https://images.unsplash.com/photo-1596462502278-27bfdc403348?auto=format&fit=crop&w=900&q=85'),
    ('CloudSoft Moisturizer','Everyday moisturizer for comfortable hydrated skin.',79900,40,'Beauty','https://images.unsplash.com/photo-1556228578-0d85b1a4d571?auto=format&fit=crop&w=900&q=85'),

    ('Halo Desk Lamp','Modern ambient desk lamp for study and work.',99900,30,'Home','https://images.unsplash.com/photo-1507473885765-e6ed057f782c?auto=format&fit=crop&w=900&q=85'),
    ('CloudSeat Lounge Chair','Comfortable modern chair for your living space.',899900,10,'Home','https://images.unsplash.com/photo-1555041469-a586c61ea9bc?auto=format&fit=crop&w=900&q=85'),
    ('CalmSpace Organizer','Minimal organizer for desks and everyday essentials.',59900,40,'Home','https://images.unsplash.com/photo-1513506003901-1e6a229e2d15?auto=format&fit=crop&w=900&q=85'),

    ('Chrono One Smart Watch','Everyday smartwatch with activity and notification features.',429900,20,'Lifestyle','https://images.unsplash.com/photo-1523275335684-37898b6baf30?auto=format&fit=crop&w=900&q=85'),
    ('Classic Canvas Tee','Simple everyday cotton t-shirt.',89900,60,'Lifestyle','https://images.unsplash.com/photo-1521572163474-6864f9cf17ab?auto=format&fit=crop&w=900&q=85'),
    ('Metro Utility Sling','Compact sling bag for phone, wallet and travel essentials.',109900,35,'Lifestyle','https://images.unsplash.com/photo-1553531384-cc64ac80f931?auto=format&fit=crop&w=900&q=85'),

    ('IronFlex Dumbbells','Adjustable dumbbells for home workouts.',249900,20,'Sports','https://images.unsplash.com/photo-1583454110551-21f2fa2afe61?auto=format&fit=crop&w=900&q=85'),
    ('CoreFlex Resistance Kit','Multi-level resistance band workout kit.',89900,45,'Sports','https://images.unsplash.com/photo-1599058917212-d750089bc07f?auto=format&fit=crop&w=900&q=85'),
    ('Sprint Training Football','Durable football for training and recreation.',79900,30,'Sports','https://images.unsplash.com/photo-1518407613690-d9fc990e795f?auto=format&fit=crop&w=900&q=85'),

    ('BuildBot STEM Kit','Creative building kit for young makers.',99900,25,'Toys & Kids','https://images.unsplash.com/photo-1596461404969-9ae70f2830c1?auto=format&fit=crop&w=900&q=85'),
    ('Rainbow Blocks Set','Colorful building blocks for creative play.',69900,40,'Toys & Kids','https://images.unsplash.com/photo-1594736797933-d0501ba2fe65?auto=format&fit=crop&w=900&q=85'),
    ('Adventure Mini Vehicles','Fun mini vehicle set for imaginative play.',54900,35,'Toys & Kids','https://images.unsplash.com/photo-1575361204480-aadea25e6e68?auto=format&fit=crop&w=900&q=85')
) AS v(name, description, price_cents, stock_qty, category, image_url)
WHERE NOT EXISTS (
    SELECT 1 FROM products p WHERE p.name = v.name
);
