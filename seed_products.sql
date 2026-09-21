-- DeepakMart demo catalog + demo seller/admin accounts.
-- Safe to run multiple times for the demo database.

ALTER TABLE products
    ADD COLUMN IF NOT EXISTS image_url TEXT;

-- Demo seller and admin. Passwords are Argon2id hashes; plaintext passwords are listed only in the demo README.
INSERT INTO users (name, email, password, role)
SELECT 'DeepakMart Seller', 'seller@deepakmart.com',
       '$argon2id$v=19$m=65536,t=3,p=2$YcihT6SFYDePtl5oNv7iEQ$Jq+QYMYe1Sv4UthEWLAD/SIK8cwHvawh2kssWrIYySI',
       'SELLER'
WHERE NOT EXISTS (
    SELECT 1 FROM users WHERE email = 'seller@deepakmart.com'
);

INSERT INTO users (name, email, password, role)
SELECT 'DeepakMart Admin', 'admin@deepakmart.com',
       '$argon2id$v=19$m=65536,t=3,p=2$jkTIsg0Q4QxwuLAln2ee8g$kfesPWa3Y54MCkfSV4ZLYwaJ3jZ0TKF6ErMAZmXayPo',
       'ADMIN'
WHERE NOT EXISTS (
    SELECT 1 FROM users WHERE email = 'admin@deepakmart.com'
);

-- Clean old demo catalog rows while keeping product 1 because it may be referenced by order #1.
DELETE FROM cart_items WHERE product_id > 1;
DELETE FROM order_items WHERE product_id > 1;
DELETE FROM orders o
WHERE NOT EXISTS (
    SELECT 1 FROM order_items oi WHERE oi.order_id = o.id
);
DELETE FROM products WHERE id > 1;

-- Keep the original product id 1 stable for the existing demo order.
UPDATE products
SET seller_id = (SELECT id FROM users WHERE email = 'seller@deepakmart.com'),
    name = 'AeroBook Pro 15',
    description = 'Slim performance laptop for study, coding and everyday productivity.',
    price_cents = 5500000,
    stock_qty = 13,
    category = 'Electronics',
    image_url = 'https://images.unsplash.com/photo-1496181133206-80ce9b88a853?auto=format&fit=crop&w=1100&q=88'
WHERE id = 1;

INSERT INTO products (seller_id, name, description, price_cents, stock_qty, category, image_url)
SELECT s.id, v.name, v.description, v.price_cents, v.stock_qty, v.category, v.image_url
FROM (SELECT id FROM users WHERE email = 'seller@deepakmart.com') s
CROSS JOIN (VALUES
 ('Pulse X1 Smartphone','Bright OLED display, fast performance and all-day battery.',2499000,21,'Electronics','https://images.unsplash.com/photo-1511707171634-5f897ff02aa9?auto=format&fit=crop&w=1100&q=88'),
 ('EchoWave ANC Headphones','Immersive over-ear audio with adaptive noise cancellation.',799900,34,'Electronics','https://images.unsplash.com/photo-1505740420928-5e560c06d30e?auto=format&fit=crop&w=1100&q=88'),
 ('Everyday Oversized Hoodie','Soft brushed cotton hoodie with a relaxed streetwear fit.',199900,29,'Fashion','https://images.unsplash.com/photo-1551488831-00ddcb6c6bd3?auto=format&fit=crop&w=1100&q=88'),
 ('Stride Run Max','Cushioned daily running shoes built for long sessions.',399900,42,'Fashion','https://images.unsplash.com/photo-1542291026-7eec264c27ff?auto=format&fit=crop&w=1100&q=88'),
 ('Urban Daypack 22L','Minimal daypack for campus, commute and weekend travel.',149900,25,'Fashion','https://images.unsplash.com/photo-1553062407-98eeb64c6a62?auto=format&fit=crop&w=1100&q=88'),
 ('Glow Vitamin C Serum','Lightweight daily serum for a fresh, hydrated-looking glow.',129900,60,'Beauty','https://images.unsplash.com/photo-1522335789203-aabd1fc54bc9?auto=format&fit=crop&w=1100&q=88'),
 ('Velvet Bloom Eau de Parfum','A warm, elegant fragrance with floral and woody notes.',189900,18,'Beauty','https://images.unsplash.com/photo-1596462502278-27bfdc403348?auto=format&fit=crop&w=1100&q=88'),
 ('CloudSoft Daily Moisturizer','Simple everyday moisturizer for soft, comfortable skin.',79900,44,'Beauty','https://images.unsplash.com/photo-1556228578-0d85b1a4d571?auto=format&fit=crop&w=1100&q=88'),
 ('Halo Desk Lamp','Warm ambient desk lamp with a clean modern silhouette.',99900,31,'Home','https://images.unsplash.com/photo-1507473885765-e6ed057f782c?auto=format&fit=crop&w=1100&q=88'),
 ('CloudSeat Lounge Chair','Soft modern lounge chair for a relaxed home setup.',899900,12,'Home','https://images.unsplash.com/photo-1555041469-a586c61ea9bc?auto=format&fit=crop&w=1100&q=88'),
 ('CalmSpace Table Organizer','Minimal desk organizer for stationery, cables and little essentials.',59900,50,'Home','https://images.unsplash.com/photo-1513506003901-1e6a229e2d15?auto=format&fit=crop&w=1100&q=88'),
 ('Chrono One Smart Watch','A clean everyday smartwatch with activity and notification tracking.',429900,20,'Lifestyle','https://images.unsplash.com/photo-1523275335684-37898b6baf30?auto=format&fit=crop&w=1100&q=88'),
 ('Classic Canvas Tee','Versatile everyday cotton tee with a relaxed fit.',89900,72,'Lifestyle','https://images.unsplash.com/photo-1521572163474-6864f9cf17ab?auto=format&fit=crop&w=1100&q=88'),
 ('Metro Utility Sling','Compact crossbody sling for phone, wallet and travel essentials.',109900,37,'Lifestyle','https://images.unsplash.com/photo-1553531384-cc64ac80f931?auto=format&fit=crop&w=1100&q=88'),
 ('IronFlex Adjustable Dumbbells','Compact adjustable dumbbells for efficient home training.',249900,24,'Sports','https://images.unsplash.com/photo-1583454110551-21f2fa2afe61?auto=format&fit=crop&w=1100&q=88'),
 ('CoreFlex Resistance Kit','Five resistance levels for home and travel workouts.',89900,56,'Sports','https://images.unsplash.com/photo-1599058917212-d750089bc07f?auto=format&fit=crop&w=1100&q=88'),
 ('Sprint Training Football','Durable training football for practice, fitness and weekend play.',79900,33,'Sports','https://images.unsplash.com/photo-1518407613690-d9fc990e795f?auto=format&fit=crop&w=1100&q=88'),
 ('BuildBot STEM Kit','Hands-on building kit designed for curious young makers.',99900,27,'Toys & Kids','https://images.unsplash.com/photo-1596461404969-9ae70f2830c1?auto=format&fit=crop&w=1100&q=88'),
 ('Rainbow Blocks Set','Colorful stacking blocks for creative play and learning.',69900,45,'Toys & Kids','https://images.unsplash.com/photo-1594736797933-d0501ba2fe65?auto=format&fit=crop&w=1100&q=88'),
 ('Adventure Mini Vehicle Set','Fun mini vehicle set for imaginative play and tiny adventures.',54900,38,'Toys & Kids','https://images.unsplash.com/photo-1575361204480-aadea25e6e68?auto=format&fit=crop&w=1100&q=88')
) AS v(name,description,price_cents,stock_qty,category,image_url) ON TRUE
WHERE NOT EXISTS (
    SELECT 1 FROM products p WHERE p.name = v.name
);

SELECT setval(
    pg_get_serial_sequence('products','id'),
    COALESCE((SELECT MAX(id) FROM products), 1),
    true
);
