#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import tornado.ioloop
import tornado.web
import tornado.escape as escape
import os
import smbus
from logging import getLogger

I2C_PORT = 1
I2C_ADDRESS_DXM = 8

bus = smbus.SMBus(I2C_PORT)

# 各種設定
settings = {
    "static_path": os.path.join(os.path.dirname(__file__), "static")
}

motorSpeeds = [0, 0]

class MainHandler(tornado.web.RequestHandler):
    """ インデックスページ表示
    """

    def get(self):
        """ インデックスページへリダイレクト
        """
        self.redirect("/index.html")

# モーターAPI
class MotorHandler(tornado.web.RequestHandler):
    """ モーター関連API
    """

    def get(self, id):
        """ モーター情報の取得
        """
        data = bus.read_i2c_block_data(I2C_ADDRESS_DXM, 0)
        self.write({
            "id": id,
            "speed": data[int(id) - 1],
        })

    def post(self, id):
        """ モーター情報の設定
        """
        json = escape.json_decode(self.request.body)
        if json is not None and json["speed"] is not None:
            motorSpeeds[int(id) - 1] = int(json["speed"])
            bus.write_i2c_block_data(I2C_ADDRESS_DXM, ord('M'), motorSpeeds)
        self.set_status(204)

if __name__ == "__main__":
    application = tornado.web.Application([
        (r"/", MainHandler),
        (r"/v1/motor/(?P<id>[0-9]+)", MotorHandler),
        (r"/(.*)", tornado.web.StaticFileHandler, dict(path=settings['static_path']))
    ])

    application.listen(8888)
    tornado.ioloop.IOLoop.current().start()

