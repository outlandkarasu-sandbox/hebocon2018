#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import tornado.ioloop
import tornado.web
import tornado.escape as escape
import os

# 各種設定
settings = {
    "static_path": os.path.join(os.path.dirname(__file__), "static")
}

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
        self.write({"id": id})

    def post(self, id):
        """ モーター情報の設定
        """
        json = escape.json_decode(self.request.body)
        self.write({"id": id})

if __name__ == "__main__":
    application = tornado.web.Application([
        (r"/", MainHandler),
        (r"/v1/motor/(?P<id>[0-9]+)", MotorHandler),
        (r"/(.*)", tornado.web.StaticFileHandler, dict(path=settings['static_path']))
    ])

    application.listen(8888)
    tornado.ioloop.IOLoop.current().start()

